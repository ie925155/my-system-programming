/**
 * Shell
 * CS 241 - Fall 2019
 */

#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#include "format.h"
#include "shell.h"
#include "vector.h"
#include "sstring.h"

typedef struct process {
    char *command;
    pid_t pid;
} process;

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

static vector *parse(const char *line)
{
    sstring *s = cstr_to_sstring(line);
    vector *v = sstring_split(s, ' ');
    sstring_destroy(s);
    return v;
}

static void run_command(vector *v, char **next)
{
    if (is_built_in(vector_get(v, 0))) {
        return;
    }
    int pid = fork();
    if (pid == -1) {
        fprintf(stderr, "%s\n", "fork failed");
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
        int status = 0;
        waitpid(pid, &status, 0);
    }
}

int shell(int argc, char *argv[]) {
    char cwd[PATH_MAX];
    char *line;
    size_t line_len = 0;

    //process p;
    char *next = NULL;
    while (true) {
        getcwd(cwd, sizeof(cwd));
        print_prompt(cwd, getpid());

        getline(&line, &line_len, stdin);

        //p.command = line;
        vector *v = parse(line);
        if (!vector_empty(v))
            run_command(v, &next);
        vector_destroy(v);
        free(line);
    }

    return 0;
}
