/**
 * Perilous Pointers
 * CS 241 - Fall 2019
 */
#include "part2-functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * (Edit this function to print out the "Illinois" lines in
 * part2-functions.c in order.)
 */
int main() {
    int value;

    value = 81;
    first_step(value);

    value = 132;
    second_step(&value);

    value = 8942;
    int *p = &value;
    double_step(&p);
    value = 15;
    char arr[10] = {0, 0, 0, 0, 0, value, 0, 0, 0};
    strange_step((char *)arr);

    char arr2[4] = {0};
    empty_step(arr2);

    char arr3[4] = {0, 0, 0, 'u'};
    two_step(arr3, arr3);

    char arr4[5] = {0};
    three_step(arr4, &arr4[2], &arr4[4]);

    char arr5[20] = {0, 0, 8, 16};
    step_step_step(arr5, arr5, arr5);

    char a = 'a';
    value = a;
    it_may_be_odd(&a, value);

    char str[20] = "aaa,CS241";
    tok_step(str);

    char str2[20] = {1, 2, 0, 0};
    the_end(str2, str2);
    return 0;
}
