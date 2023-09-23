#ifndef COUNT_DATA_TYPE_H
#define COUNT_DATA_TYPE_H

#include <stddef.h>

typedef struct count_data_type count_data_type;

typedef struct uint_based_count_data_type uint_based_count_data_type;

struct count_data_type {
    size_t (*get_val)(count_data_type* pthis);
    int (*compare_to)(count_data_type* pthis, count_data_type* pother);
};

int count_data_type_cmp(count_data_type* pthis, count_data_type* pother);

#endif