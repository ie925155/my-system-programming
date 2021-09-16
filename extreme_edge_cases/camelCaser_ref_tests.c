/**
 * Extreme Edge Cases
 * CS 241 - Fall 2019
 */
#include <stdio.h>

#include "camelCaser_ref_utils.h"

int main() {
    // Enter the string you want to test with the reference here
    char *input = "welcome to +++cs241. 33333333333! fadfhd";

    // This function prints the reference implementation output on the terminal
    print_camelCaser(input);

    // Put your expected output for the given input above
    char *arr[] = {"welcomeTo", "", "", "cs241", "33333333333", NULL};
    char **output = arr;

    // Compares the expected output you supplied with the reference output
    printf("check_output test: %d\n", check_output(input, output));

    // Feel free to add more test cases
    return 0;
}
