/**
 * Shell
 * CS 241 - Fall 2019
 */

#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <errno.h>

#include "format.h"
#include "shell.h"
#include "vector.h"
#include "sstring.h"

static bool g_received_interrupt = 0;
static vector *g_list_command;

typedef struct process {
    char *command;
    pid_t pid;
} process;

static vector *split_cmd_args(const char *cmd);

static bool is_built_in(const char *cmd) {
    if (strcmp(cmd, "cd") == 0) {
        return true;
    } else if (strcmp(cmd, "!history") == 0) {
        return true;
    } else if (strncmp(cmd, "#", 1) == 0) {
        return true;
    } else if (strncmp(cmd, "!", 1) == 0) {
        return true;
    }
    return false;
}

static bool is_need_record(const char *cmd_with_args) {
    char cmd[32] = {0x0};
    vector *v = split_cmd_args(cmd_with_args);
    memcpy(cmd, vector_get(v, 0), strlen(vector_get(v, 0)));
    vector_destroy(v);
    return (!is_built_in(cmd) || (is_built_in(cmd) && (strcmp(cmd, "cd") == 0)));
}

static vector *split_cmd_args(const char *cmd) {
    sstring *s = cstr_to_sstring(cmd);
    sstring_substitute(s, 0, "\n", "");
    vector *v = sstring_split(s, ' ');
    sstring_destroy(s);
    return v;
}

static char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

static vector *parse(const char *line)
{
#define INPUT_COMMAND_LIMIT (2)
    vector *cmds = string_vector_create();
    char *str = strdup(line);
    char *pch;
    char *str2 = strstr(str, "&");
    if (str2 != NULL && *(str2 + 1) != '&') {
        vector_push_back(cmds, str);
        goto EXIT;
    }
    pch = strtok(str, "&&||;");
    int count = 0;
    // only support x && y, x || y, x; y
    while (pch != NULL) {
        //printf("%s\n", pch);
        vector_push_back(cmds, trimwhitespace(pch));
        if (++count >= INPUT_COMMAND_LIMIT) {
            break;
        }
        pch = strtok(NULL, "&&||;");
    }
EXIT:
    free(str);
    return cmds;
}

static int32_t run_command(vector *v, char **next)
{
    int32_t ret = 0;
    const char *cmd = vector_get(v, 0);
    if (is_built_in(cmd)) {
        if (strcmp(cmd, "cd") == 0) {
            char cwd[PATH_MAX], str[PATH_MAX];
            getcwd(cwd, sizeof(cwd));
            char *path = (char *)vector_get(v, 1);
            sprintf(str, "%s/%s", cwd, path);
            ret = (path != NULL) ? chdir(str) : chdir(getenv("HOME"));
            if (ret != 0)
                fprintf(stderr, "%s: No such file or directory\n", str);
        } else if (strcmp(cmd, "!history") == 0) {
            int index = 0;
            VECTOR_FOR_EACH(g_list_command, thing, {
                print_history_line(index++, thing);
            });
        } else if (strncmp(cmd, "#", 1) == 0) {
            const int index = atoi(&cmd[1]);
            if (index >= (int)vector_size(g_list_command)) {
                print_invalid_index();
            } else {
                *next = strdup(vector_get(g_list_command, index));
            }
        } else if (strncmp(cmd, "!", 1) == 0) {
            char pattern[128] = {0x0};
            int index = 0;
            VECTOR_FOR_EACH(v, thing, {
                if (index == 0) {
                    strcat(pattern, thing + 1);
                } else {
                    strcat(pattern, thing);
                }
                strcat(pattern, " ");
                index++;
            });
            pattern[strlen(pattern)-1] = '\0';
            index = 0;
            int last_index = -1;
            VECTOR_FOR_EACH(g_list_command, thing, {
                if (strstr(thing, pattern) != NULL) {
                    last_index = index;
                }
                index++;
            });
            if (last_index < 0) {
                if (strlen(pattern) > 0) {
                    print_no_history_match();
                } else {
                    *next = strdup(vector_get(g_list_command, vector_size(g_list_command)-1));
                }
            } else {
                *next = strdup(vector_get(g_list_command, last_index));
            }
            if (*next) {
                fprintf(stderr, "%s\n", *next);
            }
        }
        return ret;
    }
    bool is_bg_process = false;
    if (vector_size(v) > 1) {
        if (strcmp(vector_get(v, vector_size(v)-1), "&") == 0) {
            is_bg_process = true;
            vector_pop_back(v);
        }
    }
    pid_t pid = fork();
    if (pid == -1) {
        print_fork_failed();
        exit(1);
    } else if (pid == 0) {
        //p.pid = getpid();
        fprintf(stderr, "Command executed by pid=%d\n", getpid());
        char *myargs[vector_size(v)+1];
        int index = 0;
        VECTOR_FOR_EACH(v, thing, {
            //fprintf(stderr, "%s\n", (char *) thing);
            myargs[index++] = strdup(thing);
        });
        myargs[index] = NULL;
        execvp(myargs[0], myargs);
        fprintf(stderr, "%s\n", "executed failed");
        exit(1);
    } else {
        if (!is_bg_process) {
            int status = 0;
            pid = waitpid(pid, &status, 0);
            if (pid != -1 && WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                //printf("process %d returned %d\n", pid, exit_status);
                ret = exit_status;
            }
        }
    }

    return ret;
}

static void sig_handler(int signum) {
    //fprintf(stderr, "catch sigal %d\n", signum);
    switch (signum) {
        case SIGINT:
            g_received_interrupt = 1;
            break;
        case SIGCHLD: {
            //int status;
            pid_t pid;
            while ((pid = waitpid((pid_t) (-1), 0, WNOHANG)) > 0) {
                //fprintf(stderr, "Child %d terminated\n", pid);
            }
        }
            break;
        default:
            break;
    }
}

int shell(int argc, char *argv[]) {

    int opt, has_history = 0, has_script = 0;
    char cwd[PATH_MAX];
    char *line = NULL;
    size_t line_len = 0;
    //process p;
    char *next = NULL;
    FILE *output_file = NULL;
    g_list_command = string_vector_create();

    while ((opt = getopt(argc, argv, "fh")) != -1) {
        switch (opt) {
            case 'h':
                has_history = 1;
                break;
            case 'f':
                has_script = 1;
                break;
            default:
                print_usage();
                exit(EXIT_FAILURE);
                break;
        }
    }
    if (has_history == 1 || has_script == 1) {
        output_file = fopen(argv[2], "a+");
        if (!output_file) {
            goto EXIT;
        }
    }

    signal(SIGINT, sig_handler);
    signal(SIGCHLD, sig_handler);

    while (true) {
        if (next != NULL) {
            memcpy(line, next, strlen(next));
            strcat(line, "\n");
            free(next);
            next = NULL;
            goto EXECUTE;
        }
        getcwd(cwd, sizeof(cwd));
        print_prompt(cwd, getpid());

        getline(&line, &line_len, (has_script) ? output_file : stdin);

        if (g_received_interrupt || feof(stdin)) {
            break;
        }
        if (has_script) {
            if (feof(output_file)) {
                printf("\n");
                break;
            }
            printf("%s", line);
        }
        //p.command = line;
        vector *cmds = NULL;
        int ret;
EXECUTE:
        cmds = parse(line);
        VECTOR_FOR_EACH(cmds, cmd, {
            vector *v = split_cmd_args(cmd);
            const char *cmd = vector_get(v, 0);
            if (strcmp(cmd, "exit") == 0) {
                vector_destroy(v);
                vector_destroy(cmds);
                goto EXIT;
            }
            if (output_file != NULL) {
                fflush(output_file);
            }
            if (!vector_empty(v))
               ret = run_command(v, &next);

            vector_destroy(v);
            // check to execute next command or not
            if (vector_size(cmds) > 1 && ret != 0) {
                if (strstr(line, "&&") != NULL) {
                    break;
                }
            }
        });
        if (vector_size(cmds) == 1 && !is_need_record(vector_get(cmds, 0))) {
            continue;
        }

        if (has_history && fwrite(line, sizeof(char), strlen(line), output_file)
            != strlen(line)) {
            fprintf(stderr, "%s\n", "write command into history.txt failed");
        }
        line[strlen(line)-1] = '\0';
        vector_push_back(g_list_command, line);
        vector_destroy(cmds);
        memset(line, 0, line_len);
    }

EXIT:
    if (line)
        free(line);
    if (output_file) {
        fclose(output_file);
    } else {
        if (has_history)
            print_history_file_error();
        else if (has_script)
            print_script_file_error();
    }
    vector_destroy(g_list_command);
    return 0;
}
