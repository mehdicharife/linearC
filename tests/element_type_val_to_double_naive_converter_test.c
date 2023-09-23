#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include "../include/element_type_val_to_double_converter.h"
#include "../include/element_type_val_to_double_naive_converter.h"
#include "../include/int_element_type.h"
#include "../include/string_element_type.h"
#include "../include/double_element_type.h"

element_type_val_to_double_converter* pconverter;

void setup() {
    pconverter = new_element_type_val_to_double_naive_converter();
}

TestSuite(element_type_val_to_double_naive_converter_test_suite, .init=setup);

struct to_dbl_conversion {
    void* input;
    double expected;
};


#define STR_TESTS_COUNT 6
#define STR_INPUTS (char*[]){"1.22", ".25", "5236.12", "10", "0", "\"2.5\""}
#define STR_EXPECTED_OUTPUTS (double[]){1.22, .25, 5236.12, 10, 0, 2.50}
ParameterizedTestParameters(element_type_val_to_double_naive_converter_test_suite, converts_strings) {
    static struct to_dbl_conversion params[STR_TESTS_COUNT];
    for(size_t k = 0; k < STR_TESTS_COUNT; k++) {
        params[k].input = cr_malloc(strlen(STR_INPUTS[k]) + 1);
        strcpy(params[k].input, STR_INPUTS[k]);
        params[k].expected = STR_EXPECTED_OUTPUTS[k];
    }

    return cr_make_param_array(struct to_dbl_conversion, params, STR_TESTS_COUNT);
}

ParameterizedTest(struct to_dbl_conversion *params, element_type_val_to_double_naive_converter_test_suite, converts_strings) {
    char* init_str = params->input;
    double got = get_element_type_val_as_double(&(params->input), new_string_element_type(), new_element_type_val_to_double_naive_converter());
    cr_expect(eq(dbl, got, params->expected));
    cr_assert(eq(str, init_str, params->input));
}


#define INT_TESTS_COUNT 6 
#define INT_INPUTS (int[]){0, 1, 132, 78, 644, 5000}
#define INT_EXPECTED_OUTPUTS (double[]){0, 1, 132, 78, 644, 5000}
ParameterizedTestParameters(element_type_val_to_double_naive_converter_test_suite, converts_ints) {
    static struct to_dbl_conversion  params[INT_TESTS_COUNT];
    for(size_t k = 0; k < INT_TESTS_COUNT; k++) {
        params[k].input = cr_malloc(sizeof(int));
        *((int*) params[k].input) = INT_INPUTS[k];
        params[k].expected = INT_EXPECTED_OUTPUTS[k];
    }
    
    return cr_make_param_array(struct to_dbl_conversion, params, INT_TESTS_COUNT);
}

ParameterizedTest(struct to_dbl_conversion* params, element_type_val_to_double_naive_converter_test_suite, converts_ints) {
    element_type* ptype = new_int_element_type();
    double actual = get_element_type_val_as_double(params->input, ptype, pconverter);
    cr_expect(eq(dbl, actual, params->expected));
}


#define double_TESTS_COUNT 6 
#define double_INPUTS (double[]){0, 1, 132, 78, 644, 5000}
#define double_EXPECTED_OUTPUTS (double[]){0, 1, 132, 78, 644, 5000}
ParameterizedTestParameters(element_type_val_to_double_naive_converter_test_suite, converts_doubles) {
    static struct to_dbl_conversion  params[double_TESTS_COUNT];
    for(size_t k = 0; k < double_TESTS_COUNT; k++) {
        params[k].input = cr_malloc(sizeof(double));
        *((double*) params[k].input) = double_INPUTS[k];
        params[k].expected = double_EXPECTED_OUTPUTS[k];
    }
    
    return cr_make_param_array(struct to_dbl_conversion, params, double_TESTS_COUNT);
}

ParameterizedTest(struct to_dbl_conversion* params, element_type_val_to_double_naive_converter_test_suite, converts_doubles) {
    element_type* ptype = new_double_element_type();
    double actual = get_element_type_val_as_double(params->input, ptype, pconverter);
    cr_expect(eq(dbl, actual, params->expected));
}


