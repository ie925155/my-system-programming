/**
 * Vector
 * CS 241 - Fall 2019
 */
#include "sstring.h"
#include "vector.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <assert.h>
#include <string.h>

struct sstring {
    vector *v;
};

sstring *cstr_to_sstring(const char *input) {
    sstring *s = malloc(sizeof(sstring));
    s->v = char_vector_create();
    for (size_t i = 0; i < strlen(input); i++) {
        vector_push_back(s->v, (void *)&input[i]);
    }
    return s;
}

char *sstring_to_cstr(sstring *input) {
    assert(input != NULL);
    const size_t size = vector_size(input->v);
    char *p = (char *)malloc(size * sizeof(char) + 1);
    int i = 0;
    for (void **it = vector_begin(input->v); it != vector_end(input->v); ++it) {
        p[i++] = (char)(*(char *)*it);
    }
    p[i] = '\0';
    return p;
}

int sstring_append(sstring *this, sstring *addition) {
    assert(this != NULL);
    for (void **it = vector_begin(addition->v); it != vector_end(addition->v);
        ++it) {
        vector_push_back(this->v, *it);
    }
    return vector_size(this->v);
}

vector *sstring_split(sstring *this, char delimiter) {
    assert(this != NULL);
    char *cstr = sstring_to_cstr(this);
    vector *v = string_vector_create();
    char *pch;
    char str_del[2];
    char *ptr = cstr;
    sprintf(str_del, "%c", delimiter);
    pch = strsep(&ptr, str_del);
    while (pch) {
        vector_push_back(v, pch);
        pch = strsep(&ptr, str_del);
    }
    free(cstr);
    return v;
}

int sstring_substitute(sstring *this, size_t offset, char *target,
                       char *substitution) {
    assert(this);
    char *cstr = sstring_to_cstr(this);
    char *start = cstr + offset;
    char *p = strstr(start, target);
    if (p != NULL) {
        int replace_start = p - cstr;
        for (int i = strlen(target); i > 0; i--) {
            //printf("%d, %c\n", i, (char)*(char *)*vector_at(this->v, replace_start));
            vector_erase(this->v, replace_start);
        }

        int idx = strlen(substitution) - 1;
        for (int i = strlen(substitution); i > 0; i--) {
            //printf("%d, %c\n", i, (char)*(char *)*vector_at(this->v, i));
            vector_insert(this->v, replace_start, &substitution[idx--]);
        }
    }
    free(cstr);
    return (p != NULL) ? 0 : -1;
}

char *sstring_slice(sstring *this, int start, int end) {
    char *str = malloc(sizeof(char) * (end - start) + 1);

    int idx = 0;
    for (int i = start; i < end; i++) {
        str[idx++] = (char)*(char *)*vector_at(this->v, i);
    }
    str[idx] = '\0';
    return str;
}

void sstring_destroy(sstring *this) {
    vector_destroy(this->v);
    free(this);
}
