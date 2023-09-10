/*
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include <stdio.h>
#include <string.h>

#define STRINGS_COUNT 2 
#define STRINGS (char*[]){"Foo", "Bar"}

ParameterizedTestParameters(test_suite, test_str) {
    static char* strings[STRINGS_COUNT];
    
    for(size_t k = 0; k < STRINGS_COUNT; k++) {
        strings[k] = cr_malloc(strlen(STRINGS[k]));
        strcpy(strings[k], STRINGS[k]);
    }

    return cr_make_param_array(char*, strings, STRINGS_COUNT);
}

ParameterizedTest(char* *pstring, test_suite, test_str) {
    printf("%s\n", *pstring);
}


ParameterizedTestParameters(test_suite, test_int) {
    static int numbers[] = {1, 2};
    size_t numbers_count = sizeof(numbers)/sizeof(int);

    return cr_make_param_array(int, numbers, numbers_count);
}

ParameterizedTest(int* pnum, test_suite, test_int) {
    printf("%d\n", *pnum);
}
*/