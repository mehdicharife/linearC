#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/element_type_eloquence_cmp.h"
#include "../include/double_element_type.h"
#include "../include/int_element_type.h"



TestSuite(element_type_comparator_test_suite);

Test(element_type_eloquence_cmp_test_suite, same_types_are_equal) {
    element_type* ptype1 = new_double_element_type();
    element_type* ptype2 = new_double_element_type();

    int comparison_result = element_type_eloquence_cmp(ptype1, ptype2);
    cr_expect(eq(int, comparison_result, 0)); 
}

Test(element_type_eloquence_cmp_test_sute, double_is_more_eloquent_than_int) {
    element_type* pdbl_type = new_double_element_type();
    element_type* pint_type = new_int_element_type();

    int comparison_result = element_type_eloquence_cmp(pdbl_type, pint_type);
    cr_expect(gt(int, comparison_result, 0));
 }

 Test(element_type_eloquence_cmp_test_suite, all_types_are_more_eloquent_than_least_eloquent) {
    element_type** supported_types;
    size_t supported_types_count;
    set_to_supported_element_types(&supported_types, &supported_types_count);

    for(size_t k = 0; k < supported_types_count; k++) {
        int comparison_result = element_type_eloquence_cmp(supported_types[k], new_least_eloquent());
        cr_expect(gt(int, comparison_result, 0));
    }
 }