#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/type_distribution.h"
#include "../include/uniform_type_distribution.h"
#include "../include/type_per_track_distribution.h"
#include "../include/double_element_type.h"
#include "../include/int_element_type.h"


Test(type_distribution_from_types_array_test_suite, generate_uniform_type_distribution_from_uniform_array) {
    element_type* ptype = new_double_element_type();
    size_t type_count = 3;
    element_type** types = malloc(type_count*sizeof(element_type*));
    for(size_t k = 0; k < type_count; k++) {
        types[k] = ptype;
    }

    type_distribution* expected = new_uniform_type_distribution(ptype);
    type_distribution* got = new_type_distribution_from_types_array(types, type_count);

    cr_expect(expected->equals(expected, got));
}



Test(type_distribution_from_types_array_test_suite, generate_type_per_col_distribution_from_mixed_array) {
    size_t type_count = 3;
    element_type** types = malloc(type_count*sizeof(element_type*));
    for(size_t k = 0; k < type_count; k++) {
        types[k] = (k == 0) ? new_double_element_type() : new_int_element_type();
    }

    type_distribution* expected = new_type_per_track_distribution(1, types, type_count);
    type_distribution* got = new_type_distribution_from_types_array(types, type_count);


    cr_expect(expected->equals(expected, got));
}