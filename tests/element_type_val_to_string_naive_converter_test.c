#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include "../include/element_type_val_to_string_naive_converter.h"
#include "../include/int_element_type.h"
#include "../include/double_element_type.h"
#include "../include/string_element_type.h"
#include <stdio.h>
#include <string.h>


element_type_val_to_string_converter* pconverter;

void setup() {
    pconverter = new_element_type_val_to_string_naive_converter();
}

TestSuite(element_type_val_to_string_naive_converter_test_suite, .init=setup);

struct conversion_parameters {
    void* pval;
    char* expected;
};

#define INT_VALUES_COUNT 5
#define VALUES (int[]){0, 1, 25, 784, 40}
#define STRINGS (char*[]){"0", "1", "25", "784", "40"}
ParameterizedTestParameters(element_type_val_to_string_naive_converter_test_suite, converts_ints) { 
    static struct conversion_parameters params[5];
    for(size_t k = 0; k < INT_VALUES_COUNT; k++) {
        params[k].pval = cr_malloc(sizeof(int));
        *((int*) params[k].pval) = VALUES[k];
        params[k].expected = cr_malloc(strlen(STRINGS[k]) + 1);
        strcpy(params[k].expected, STRINGS[k]);
    }
    return cr_make_param_array(struct conversion_parameters, params, INT_VALUES_COUNT);
}

ParameterizedTest(struct conversion_parameters *params, element_type_val_to_string_naive_converter_test_suite, converts_ints) {
    element_type* ptype = new_int_element_type();

    char* actual = get_element_type_val_as_string(params->pval, ptype, (element_type_val_to_string_converter*) pconverter);
    cr_assert(eq(str, actual, params->expected));
}




#define DBL_VALUES_COUNT 5
#define DBL_VALUES (double[]){0.0, 1.0, 25.23, 784.0, 40.235}
#define DBL_STRINGS (char*[]){"0.000000", "1.000000", "25.230000", "784.000000", "40.235000"}
ParameterizedTestParameters(element_type_val_to_string_naive_converter_test_suite, converts_doubles) { 
    static struct conversion_parameters params[5];
    for(size_t k = 0; k < DBL_VALUES_COUNT; k++) {
        params[k].pval = cr_malloc(sizeof(double));
        *((double*) params[k].pval) = DBL_VALUES[k];
        params[k].expected = cr_malloc(strlen(DBL_STRINGS[k]) + 1);
        strcpy(params[k].expected, DBL_STRINGS[k]);
    }
    return cr_make_param_array(struct conversion_parameters, params, DBL_VALUES_COUNT);
}

ParameterizedTest(struct conversion_parameters *params, element_type_val_to_string_naive_converter_test_suite, converts_doubles) {
    element_type* ptype = new_double_element_type();

    char* actual = get_element_type_val_as_string(params->pval, ptype, pconverter);
    cr_assert(eq(str, actual, params->expected));
}


#define STR_VALUES_COUNT 5
#define STR_VALUES (char*[]){"Foo", "Bar", "lorem", "784.0", "4m40.234dfd5"}
#define STR_STRINGS (char*[]){"Foo", "Bar", "lorem", "784.0", "4m40.234dfd5"}
ParameterizedTestParameters(element_type_val_to_string_naive_converter_test_suite, converts_strings) { 
    static struct conversion_parameters params[5];
    for(size_t k = 0; k < STR_VALUES_COUNT; k++) {
        params[k].pval = cr_malloc(sizeof(double));
        params[k].pval = cr_malloc(strlen(STR_VALUES[k]) + 1);
        strcpy(params[k].pval, STR_VALUES[k]);

        params[k].expected = cr_malloc(strlen(STR_STRINGS[k]) + 1);
        strcpy(params[k].expected, STR_STRINGS[k]);
    }
    return cr_make_param_array(struct conversion_parameters, params, STR_VALUES_COUNT);
}

ParameterizedTest(struct conversion_parameters *params, element_type_val_to_string_naive_converter_test_suite, converts_strings) {
    element_type* ptype = new_string_element_type();
    pconverter->input = NULL;
    char* actual = get_element_type_val_as_string(params->pval, ptype, pconverter);
    cr_assert(eq(str, actual, params->expected));
}