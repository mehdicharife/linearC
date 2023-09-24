#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include "../include/element_type_val_to_int_converter.h"
#include "../include/element_type_val_to_int_naive_converter.h"
#include "../include/int_element_type.h"
#include "../include/double_element_type.h"
#include "../include/string_element_type.h"



element_type_val_to_int_converter* pconverter;

void setup() {
    pconverter = new_element_type_val_to_int_naive_converter();
}

TestSuite(element_type_val_to_int_naive_converter_test_suite, .init=setup);


struct to_int_conversion {
    void* input;
    int expected;
};


#define STRINGS_TESTS_COUNT 6
#define STRINGS_INPUT (char*[]){"0", "1", "2", "36", "2.5", "600"}
#define STRINGS_EXPECTED_OUTPUT (int[]){0, 1, 2, 36, 2, 600}
ParameterizedTestParameters(element_type_val_to_int_naive_converter_test_suite, converts_strings) {
    static struct to_int_conversion params[STRINGS_TESTS_COUNT];
    for(size_t k = 0; k < STRINGS_TESTS_COUNT; k++) {
        params[k].input = cr_malloc(strlen(STRINGS_INPUT[k]) + 1);
        strcpy(params[k].input, STRINGS_INPUT[k]);
        params[k].expected = STRINGS_EXPECTED_OUTPUT[k];
    }

    return cr_make_param_array(struct to_int_conversion, params, STRINGS_TESTS_COUNT);
}

ParameterizedTest(struct to_int_conversion *params, element_type_val_to_int_naive_converter_test_suite, converts_strings) {
    element_type* ptype = new_string_element_type();
    int actual = get_element_type_val_as_int(&(params->input), ptype, pconverter);
    cr_assert(eq(int, actual, params->expected));
}


#define DOUBLES_TESTS_COUNT 6
#define DOUBLES_INPUT (double[]){.0, 1.0, 235.241, .36, 600, 90.01}
#define DOUBLES_EXPECTED_OUTPUT (int[]){0, 1, 235, 0, 600, 90}
ParameterizedTestParameters(element_type_val_to_int_naive_converter_test_suite, converts_doubles) {
    static struct to_int_conversion params[DOUBLES_TESTS_COUNT];
    for(size_t k = 0; k < DOUBLES_TESTS_COUNT; k++) {
        params[k].input = cr_malloc(sizeof(double));
        *((double*) params[k].input) = DOUBLES_INPUT[k];
        params[k].expected = DOUBLES_EXPECTED_OUTPUT[k];
    }

    return cr_make_param_array(struct to_int_conversion, params, DOUBLES_TESTS_COUNT);
}

ParameterizedTest(struct to_int_conversion *params, element_type_val_to_int_naive_converter_test_suite, converts_doubles) {
    element_type* ptype = new_double_element_type();
    int actual = get_element_type_val_as_int(params->input, ptype, pconverter);
    cr_assert(eq(int, actual, params->expected));
}



#define INT_TESTS_COUNT 6
#define INT_INPUTS (int[]){0, 1, 235, 2, 600, 90}
#define INT_EXPECTED_OUTPUT (int[]){0, 1, 235, 2, 600, 90}
ParameterizedTestParameters(element_type_val_to_int_naive_converter_test_suite, converts_ints) {
    static struct to_int_conversion params[INT_TESTS_COUNT];
    for(size_t k = 0; k < INT_TESTS_COUNT; k++) {
        params[k].input = cr_malloc(sizeof(int));
        *((int*) params[k].input) = INT_INPUTS[k];
        params[k].expected = INT_EXPECTED_OUTPUT[k];
    }

    return cr_make_param_array(struct to_int_conversion, params, INT_TESTS_COUNT);
}

ParameterizedTest(struct to_int_conversion *params, element_type_val_to_int_naive_converter_test_suite, converts_ints) {
    element_type* ptype = new_int_element_type();
    int actual = get_element_type_val_as_int(params->input, ptype, pconverter);
    cr_assert(eq(int, actual, params->expected));
}