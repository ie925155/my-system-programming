/**
 * Vector
 * CS 241 - Fall 2019
 */
#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>


static void Test_char_vector(void) {
    vector *v = char_vector_create();

    char *t = "abcdef";
    for (size_t i = 0; i < strlen(t); i++) {
        vector_push_back(v, &t[i]);
    }
    assert(vector_size(v) == 6);

    vector_pop_back(v);
    assert(vector_size(v) == 5);

    int i = 0;
    for (void **it = vector_begin(v); it != vector_end(v); ++it) {
        assert(t[i++] == (char)(*(char *)*it));
        //printf("%p, %c\n", *it, (char)(*(char *)*it));
    }

    vector_destroy(v);
    printf("passed %s\n", __FUNCTION__);
}

int main(int argc, char *argv[]) {

    Test_char_vector();

    return 0;
}
