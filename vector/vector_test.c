/**
 * Vector
 * CS 241 - Fall 2019
 */
#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

static void Test_char_vector(void) {
    printf("%s -> ", __FUNCTION__);

    vector *v = char_vector_create();

    char *t = "abcdefghij";
    for (size_t i = 0; i < strlen(t); i++) {
        vector_push_back(v, &t[i]);
    }
    assert(vector_size(v) == 10);

    vector_pop_back(v);
    assert(vector_size(v) == 9);

    int i = 0;
    for (void **it = vector_begin(v); it != vector_end(v); ++it) {
        assert(t[i++] == (char)(*(char *)*it));
        //printf("%p, %c\n", *it, (char)(*(char *)*it));
    }

    vector_resize(v, 20);
    assert(vector_size(v) == 20);

    vector_resize(v, 5);
    assert(vector_size(v) == 5);

    vector_reserve(v, 30);
    assert(vector_capacity(v) >= 30);

    assert(vector_empty(v) == false);

    void **it;
    it = vector_at(v, 0);
    assert(t[0] == (char)(*(char *)*it));
    it = vector_at(v, 1);
    assert(t[1] == (char)(*(char *)*it));
    it = vector_at(v, 2);
    assert(t[2] == (char)(*(char *)*it));
    it = vector_at(v, 3);
    assert(t[3] == (char)(*(char *)*it));

    vector_set(v, 0, "s");
    char *a = (char *)vector_get(v, 0);
    assert(*a == 's');

    a = (char *)vector_get(v, 100);
    assert(a == NULL);

    it = vector_front(v);
    assert('s' == (char)(*(char *)*it));

    it = vector_back(v);
    assert(t[vector_size(v)-1] == (char)(*(char *)*it));

    vector_insert(v, 1, "a");
    assert(*(char *)vector_get(v, 1) == 'a');
    assert(*(char *)vector_get(v, 0) == 's');
    assert(*(char *)vector_get(v, 2) == 'b');

    vector_erase(v, 1);
    assert(*(char *)vector_get(v, 0) == 's');
    assert(*(char *)vector_get(v, 1) == 'b');
    assert(*(char *)vector_get(v, 2) == 'c');

    vector_clear(v);
    assert(vector_size(v) == 0);

    vector_destroy(v);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}


static void Test_double_vector(void) {
    printf("%s -> ", __FUNCTION__);

    vector *v = double_vector_create();

    double t[] = {1.2, 2.4, 3.6, 4.8, 5.0, 6.7, 7.9, 8.178, 9.44, 10.0};
    for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) {
       vector_push_back(v, &t[i]);
    }
    assert(vector_size(v) == 10);

    vector_pop_back(v);
    assert(vector_size(v) == 9);

    int i = 0;
    for (void **it = vector_begin(v); it != vector_end(v); ++it) {
        assert(t[i++] == (double)(*(double *)*it));
        //printf("%p, %c\n", *it, (double)(*(double *)*it));
    }

    vector_resize(v, 20);
    assert(vector_size(v) == 20);

    vector_resize(v, 5);
    assert(vector_size(v) == 5);

    vector_reserve(v, 30);
    assert(vector_capacity(v) >= 30);

    assert(vector_empty(v) == false);

    void **it;
    it = vector_at(v, 0);
    assert(t[0] == (double)(*(double *)*it));
    it = vector_at(v, 1);
    assert(t[1] == (double)(*(double *)*it));
    it = vector_at(v, 2);
    assert(t[2] == (double)(*(double *)*it));
    it = vector_at(v, 3);
    assert(t[3] == (double)(*(double *)*it));

    double value = 9.99;
    vector_set(v, 0, &value);
    double *a = (double *)vector_get(v, 0);
    assert(*a == value);

    a = (double *)vector_get(v, 100);
    assert(a == NULL);

    it = vector_front(v);
    assert(value == (double)(*(double *)*it));

    it = vector_back(v);
    assert(t[vector_size(v)-1] == (double)(*(double *)*it));

    value = 8.88;
    vector_insert(v, 1, &value);
    assert(*(double *)vector_get(v, 1) == value);
    assert(*(double *)vector_get(v, 0) == 9.99);
    assert(*(double *)vector_get(v, 2) == 2.4);

    vector_erase(v, 1);
    assert(*(double *)vector_get(v, 0) == 9.99);
    assert(*(double *)vector_get(v, 1) == 2.4);
    assert(*(double *)vector_get(v, 2) == 3.6);

    vector_clear(v);
    assert(vector_size(v) == 0);

    vector_destroy(v);
    
    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

int main(int argc, char *argv[]) {

    Test_char_vector();

    Test_double_vector();

    return 0;
}
