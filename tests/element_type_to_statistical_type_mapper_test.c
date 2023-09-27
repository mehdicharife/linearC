#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/element_type_to_statistical_type_mapper.h"
#include "../include/element_type_to_statistical_type_naive_mapper.h"
#include "../include/double_element_type.h"
#include "../include/int_element_type.h"
#include "../include/string_element_type.h"


element_type_to_statistical_type_mapper* pmapper;

void setup() {
    pmapper = new_element_type_to_statistical_type_naive_mapper();
}

TestSuite(element_type_to_statistical_type_naive_mapper_test_suite, .init=setup);


Test(element_type_to_statistical_type_naive_mapper_test_suite, maps_double_element_type_to_continuous_data_type) {
    element_type* ptype = new_double_element_type();
    statistical_data_type stats_type = get_statistical_data_type_from_element_type(ptype, pmapper);
    cr_assert(eq(int, stats_type, continuous));
}

Test(element_type_to_statistical_type_naive_mapper_test_suite, maps_int_element_type_to_count_data_type) {
    element_type* ptype = new_int_element_type();
    statistical_data_type actual = get_statistical_data_type_from_element_type(ptype, pmapper);
    cr_assert(eq(int, actual, count));

}

Test(element_type_to_statistical_type_naive_mapper_test_suite, maps_string_element_type_to_nominal_data_type) {
    element_type* ptype = new_string_element_type();
    statistical_data_type actual = get_statistical_data_type_from_element_type(ptype, pmapper);
    cr_assert(eq(int, actual, nominal));
}