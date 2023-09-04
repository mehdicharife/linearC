#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/element_type.h"
#include "../include/double_element_type.h"
#include "../include/int_element_type.h"

element_type** types;
int type_count;

void setup(void) {
    type_count = 2;
    types = malloc(type_count*sizeof(element_type*));
    types[0] = new_double_element_type();
    types[1] = new_int_element_type();
}


TestSuite(get_element_type_from_str_test_suite, .init=setup);

Test(get_element_type_from_str_test_suite, handles_double) {
    char* double_as_str = "5.2";
    element_type* ptype = get_element_type_from_str(double_as_str, types, type_count);
    cr_assert(eq(ptr, ptype, types[0]));
}

Test(get_element_type_from_str_test_suite, handles_int) {
    char* int_as_str = "5";
    element_type* ptype = get_element_type_from_str(int_as_str, types, type_count);
    cr_assert(eq(ptr, ptype, types[1]));
}


