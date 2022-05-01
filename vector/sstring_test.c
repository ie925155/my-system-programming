/**
 * Vector
 * CS 241 - Fall 2019
 */
#include "sstring.h"

#include <assert.h>
#include <string.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

static void Test_cstr_sstring(void)
{
    printf("%s -> ", __FUNCTION__);

    char *expect, *cstr;
    expect = "Frequently Asked Questions";
    sstring *s = cstr_to_sstring(expect);
    cstr = sstring_to_cstr(s);
    //printf("cstr: %s\n", cstr);
    //printf("expect: %s\n", expect);
    assert(strcmp(cstr, expect) == 0);

    free(cstr);
    sstring_destroy(s);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

static void Test_cstr_sstring2(void)
{
    printf("%s -> ", __FUNCTION__);

    char *expect, *cstr;
    expect = "The username of the future. Nametag is your universal username";
    sstring *s = cstr_to_sstring(expect);
    cstr = sstring_to_cstr(s);
    assert(strcmp(cstr, expect) == 0);

    free(cstr);
    sstring_destroy(s);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

static void Test_sstring_append(void)
{
    printf("%s -> ", __FUNCTION__);

    sstring *str1 = cstr_to_sstring("abc");
    sstring *str2 = cstr_to_sstring("def");
    int len = sstring_append(str1, str2);
    assert(len == 6);

    char *expect = "abcdef";
    char *result = sstring_to_cstr(str1);
    assert(strcmp(result, expect) == 0);

    free(result);
    sstring_destroy(str1);
    sstring_destroy(str2);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

static void Test_sstring_split(void) {
    printf("%s -> ", __FUNCTION__);


    sstring *s = cstr_to_sstring("abcdeefg");
    vector *v = sstring_split(s, 'e');

    assert(vector_size(v) == 3);

    char *expect[] = {"abcd", "", "fg"};
    int count = 0;
    for (void **it = vector_begin(v); it != vector_end(v); ++it) {
        assert(strcmp(*it, expect[count++]) == 0);
    }

    vector_destroy(v);
    sstring_destroy(s);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

static void Test_sstring_split2(void) {
    printf("%s -> ", __FUNCTION__);

    sstring *s = cstr_to_sstring("This is a sentence.");
    vector *v = sstring_split(s, ' ');

    assert(vector_size(v) == 4);

    char *expect[] = {"This", "is", "a", "sentence."};
    int count = 0;
    for (void **it = vector_begin(v); it != vector_end(v); ++it) {
        //printf("*it=%s\n", *it);
        assert(strcmp(*it, expect[count++]) == 0);
    }

    vector_destroy(v);
    sstring_destroy(s);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

static void Test_sstring_replace(void) {
    printf("%s -> ", __FUNCTION__);

    sstring *replace_me = cstr_to_sstring("This is a {} day, {}!");
    sstring_substitute(replace_me, 18, "{}", "friend");

    char *expect = "This is a {} day, friend!";
    char *result = sstring_to_cstr(replace_me);
    //printf("result=%s\n", result);

    assert(strcmp(result, expect) == 0);

    free(result);

    sstring_substitute(replace_me, 0, "{}", "good");

    expect = "This is a good day, friend!";
    result = sstring_to_cstr(replace_me);

    assert(strcmp(result, expect) == 0);

    free(result);

    sstring_destroy(replace_me);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

static void Test_sstring_slice(void) {
    printf("%s -> ", __FUNCTION__);

    sstring *slice_me = cstr_to_sstring("1234567890");


    char *expect = "345";
    char *result = sstring_slice(slice_me, 2, 5);

    assert(strcmp(result, expect) == 0);

    sstring_destroy(slice_me);
    free(result);

    printf(ANSI_COLOR_GREEN "passed" ANSI_COLOR_RESET "\n");
}

int main(int argc, char *argv[]) {

    for (int i = 0; i < 1; i++) {
        Test_cstr_sstring();

        Test_cstr_sstring2();

        Test_sstring_append();

        Test_sstring_split();

        Test_sstring_split2();

        Test_sstring_replace();

        Test_sstring_slice();
    }

    return 0;
}
