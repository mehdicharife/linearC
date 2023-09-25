#include "../include/uint_based_count_data_type.h"
#include <stdlib.h>
#include <stdio.h>

count_data_type* new_uint_based_count_data_type(size_t val) {
    uint_based_count_data_type* ret = malloc(sizeof(uint_based_count_data_type));
    ret->val = val;

    ret->parent.get_val = uint_based_count_data_type_get_val;
    ret->parent.compare_to = count_data_type_cmp;
    return (count_data_type*) ret;
}

size_t uint_based_count_data_type_get_val(count_data_type* pthis) {
    return ((uint_based_count_data_type*) pthis)->val;
}