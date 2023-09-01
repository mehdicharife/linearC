#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/element_type_comparator.h"
#include "../include/double_element_type.h"


element_type* (*type_factory)();

void setup(void) {
    type_factory = new_double_element_type;
}

TestSuite(element_type_comparator_test_suite, .init=setup);

Test(element_type_comparator_test_suite, equality) {
    element_type* ptype1 = type_factory();
    element_type* ptype2 = type_factory();

    int comparison_result = element_type_cmpr_eloquence(ptype1, ptype2);
    cr_expect(eq(int, comparison_result, 0)); 
}