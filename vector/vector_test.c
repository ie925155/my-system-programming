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


static void Test_float_vector(void) {
    printf("%s -> ", __FUNCTION__);

    vector *v = float_vector_create();

    float t[] = {1.2, 2.4, 3.6, 4.8, 5.0, 6.7, 7.9, 8.178, 9.44, 10.0};
    for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) {
       vector_push_back(v, &t[i]);
    }
    assert(vector_size(v) == 10);

    vector_pop_back(v);
    assert(vector_size(v) == 9);

    int i = 0;
    for (void **it = vector_begin(v); it != vector_end(v); ++it) {
        assert(t[i++] == (float)(*(float *)*it));
        //printf("%p, %c\n", *it, (float)(*(float *)*it));
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
    assert(t[0] == (float)(*(float *)*it));
    it = vector_at(v, 1);
    assert(t[1] == (float)(*(float *)*it));
    it = vector_at(v, 2);
    assert(t[2] == (float)(*(float *)*it));
    it = vector_at(v, 3);
    assert(t[3] == (float)(*(float *)*it));

    float value = 9.99;
    vector_set(v, 0, &value);
    float *a = (float *)vector_get(v, 0);
    assert(*a == value);

    a = (float *)vector_get(v, 100);
    assert(a == NULL);

    it = vector_front(v);
    assert(value == (float)(*(float *)*it));

    it = vector_back(v);
    assert(t[vector_size(v)-1] == (float)(*(float *)*it));

    value = 8.88;
    vector_insert(v, 1, &value);
    assert(*(float *)vector_get(v, 1) == value);
    assert(*(float *)vector_get(v, 0) == (float)9.99);
    assert(*(float *)vector_get(v, 2) == (float)2.4);

    vector_erase(v, 1);
    assert(*(float *)vector_get(v, 0) == (float)9.99);
    assert(*(float *)vector_get(v, 1) == (float)2.4);
    assert(*(float *)vector_get(v, 2) == (float)3.6);

    vector_clear(v);
    assert(vector_size(v) == 0);

    vector_destroy(v);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

static void Test_int_vector(void) {
    printf("%s -> ", __FUNCTION__);

    vector *v = int_vector_create();

    int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) {
       vector_push_back(v, &t[i]);
    }
    assert(vector_size(v) == 10);

    vector_pop_back(v);
    assert(vector_size(v) == 9);

    int i = 0;
    for (void **it = vector_begin(v); it != vector_end(v); ++it) {
        assert(t[i++] == (int)(*(int *)*it));
        //printf("%p, %c\n", *it, (int)(*(int *)*it));
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
    assert(t[0] == (int)(*(int *)*it));
    it = vector_at(v, 1);
    assert(t[1] == (int)(*(int *)*it));
    it = vector_at(v, 2);
    assert(t[2] == (int)(*(int *)*it));
    it = vector_at(v, 3);
    assert(t[3] == (int)(*(int *)*it));

    int value = 9;
    vector_set(v, 0, &value);
    int *a = (int *)vector_get(v, 0);
    assert(*a == value);

    a = (int *)vector_get(v, 100);
    assert(a == NULL);

    it = vector_front(v);
    assert(value == (int)(*(int *)*it));

    it = vector_back(v);
    assert(t[vector_size(v)-1] == (int)(*(int *)*it));

    value = 8;
    vector_insert(v, 1, &value);
    assert(*(int *)vector_get(v, 1) == value);
    assert(*(int *)vector_get(v, 0) == 9);
    assert(*(int *)vector_get(v, 2) == 2);

    vector_erase(v, 1);
    assert(*(int *)vector_get(v, 0) == 9);
    assert(*(int *)vector_get(v, 1) == 2);
    assert(*(int *)vector_get(v, 2) == 3);

    vector_clear(v);
    assert(vector_size(v) == 0);

    vector_destroy(v);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

static void Test_string_vector(void) {
    printf("%s -> ", __FUNCTION__);

    vector *v = string_vector_create();

    char *t[] = {"test1", "test22", "test333", "test4444", "test55555",
        "test666666", "test7777777", "test88888888", "test999999999",
        "test10101010101010101010"};
    for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) {
       vector_push_back(v, t[i]);
    }
    assert(vector_size(v) == 10);

    vector_pop_back(v);
    assert(vector_size(v) == 9);

    int i = 0;
    for (void **it = vector_begin(v); it != vector_end(v); ++it) {
        assert(strcmp(t[i++], *it) == 0);
        //printf("%p, %s\n", *it, (char *)*it);
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
    assert(strcmp(t[0], *it) == 0);
    it = vector_at(v, 1);
    assert(strcmp(t[1], *it) == 0);
    it = vector_at(v, 2);
    assert(strcmp(t[2], *it) == 0);
    it = vector_at(v, 3);
    assert(strcmp(t[3], *it) == 0);

    char *value = "sheldon test";
    vector_set(v, 0, value);
    char *a = (char *)vector_get(v, 0);
    assert(strcmp(value, a) == 0);

    a = (char *)vector_get(v, 100);
    assert(a == NULL);

    it = vector_front(v);
    assert(strcmp(value ,*it) == 0);

    it = vector_back(v);
    assert(strcmp(t[vector_size(v)-1], *it) == 0);

    value = "fish insert here";
    vector_insert(v, 1, value);
    assert(strcmp(value, vector_get(v, 1)) == 0);
    assert(strcmp("sheldon test", vector_get(v, 0)) == 0);
    assert(strcmp("test22", vector_get(v, 2)) == 0);

    vector_erase(v, 1);
    assert(strcmp("sheldon test", vector_get(v, 0)) == 0);
    assert(strcmp("test22", vector_get(v, 1)) == 0);
    assert(strcmp("test333", vector_get(v, 2)) == 0);

    vector_clear(v);
    assert(vector_size(v) == 0);

    vector_destroy(v);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

int main(int argc, char *argv[]) {

    Test_char_vector();

    Test_double_vector();

    Test_float_vector();

    Test_int_vector();

    Test_string_vector();

    return 0;
}
