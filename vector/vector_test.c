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
    assert('e' == (char)(*(char *)*it));

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
    printf("passed %s\n", __FUNCTION__);
}

int main(int argc, char *argv[]) {

    Test_char_vector();

    return 0;
}
