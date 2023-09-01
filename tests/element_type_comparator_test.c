#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/element_type_comparator.h"
#include "../include/double_element_type.h"
#include "../include/int_element_type.h"



TestSuite(element_type_comparator_test_suite);

Test(element_type_comparator_test_suite, equality) {
    element_type* ptype1 = new_double_element_type();
    element_type* ptype2 = new_double_element_type();

    int comparison_result = element_type_cmpr_eloquence(ptype1, ptype2);
    cr_expect(eq(int, comparison_result, 0)); 
}

Test(element_type_comparator_test_sute, double_is_more_eloquent_than_int) {
    element_type* pdbl_type = new_double_element_type();
    element_type* pint_type = new_int_element_type();

    int comparison_result = element_type_cmpr_eloquence(pdbl_type, pint_type);
    cr_expect(gt(int, comparison_result, 0));
 }