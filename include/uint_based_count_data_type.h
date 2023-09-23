#ifndef UINT_BASED_COUNT_DATA_TYPE_H
#define UINT_BASED_COUNT_DATA_TYPE_H

#include "count_data_type.h"

struct uint_based_count_data_type {
    count_data_type parent;
    size_t val;
};

count_data_type* new_uint_based_count_data_type(size_t val);
size_t uint_based_count_data_type_get_val(count_data_type* pthis);


#endif