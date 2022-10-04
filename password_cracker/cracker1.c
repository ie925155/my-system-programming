/**
 * Password Cracker
 * CS 241 - Fall 2019
 */
#include "cracker1.h"
#include "format.h"
#include "utils.h"
#include "tpool.h"

int start(size_t thread_count) {
    // TODO your code here, make sure to use thread_count!
    // Remember to ONLY crack passwords in other threads
    tpool_create(4);

    return 0; // DO NOT change the return code since AG uses it to check if your
              // program exited normally
}
