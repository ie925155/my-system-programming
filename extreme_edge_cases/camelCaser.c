/**
 * Extreme Edge Cases
 * CS 241 - Fall 2019
 */
#include "camelCaser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static char *g_tokens[4096] = {NULL};


static void trim(char *s);
static void trans_to_camel(char *s);

static void trim(char *s) {
  char *p = s;
  int l = strlen(p);

  if (l == 0) {
    return;
  }

  while(isspace(p[l - 1])) p[--l] = '\0';
  while(*p && isspace(*p)) ++p, --l;

  memmove(s, p, l + 1);
}

static void trans_to_camel(char *s) {
  printf("trans_to_camel=%s\n", s);

  if (s == NULL || strlen(s) == 0) {
    return;
  }

  char *p = s;
  char *d = p;

  while(*p != '\0') {
    bool is_next_token = false;
    while (isspace(*p)) {
      p++;
      is_next_token = true;
    }
    if (is_next_token) {
      char *temp = p;
      while (*temp != '\0' && !isspace(*temp) && !isalpha(*temp)) {
        *d++ = *temp++;
      }
      //if (isalpha(*temp) || *temp == '\0') {
       p = temp;
      //}
    }
    if (*p == '\0') break;
    if (isspace(*p)) continue;
    *p = is_next_token ? toupper(*p) : tolower(*p);
    *d++ = *p++;
  }
  *d = '\0';

  printf("after trans_to_camel=%s\n", s);
}

char **camel_caser(const char *input_str) {
    if (input_str == NULL) {
      return NULL;
    }

    printf("input=%s\n", input_str);

    char *input_str2 = (char *)strdup(input_str);
    char *input_str2_bak = input_str2;
    char *next = input_str2;

    char *token;
    int token_count = 0;
    while (*next != '\0') {
      if (ispunct(*next)) {
        //printf("punct=%c\n", *next);
        char *start = input_str2;
        if (ispunct(*input_str2)) {
           start++;
        }
        //printf("substring diff len=%ld\n", next-start);
        if (next - start <= 0) {
            token = "";
            g_tokens[token_count++] = token;
            //printf("token=\"%s\" strlen=%lu\n", token, strlen(token));
            input_str2 = next;
            next++;
            continue;
        }
        int token_len = next - start;
        token = malloc(token_len + 1);
        memcpy(token, start, token_len);
        token[token_len] = '\0';
        g_tokens[token_count++] = token;
        //printf("token=\"%s\" strlen=%lu\n", token, strlen(token));
        input_str2 = next;
        //printf("str=%s\n", input_str2);
      }
      next++;
    }

    g_tokens[token_count] = NULL;

    for (int i = 0; i < token_count; i++) {
      trim(g_tokens[i]);
      trans_to_camel(g_tokens[i]);
    }

    free(input_str2_bak);

    return g_tokens;
}

void destroy(char **result) {
    while (*result != NULL) {
      //printf("free \"%s\"\n", *result);
      if (strlen(*result) > 0)
        free(*result);
      result++;
    }
    return;
}
