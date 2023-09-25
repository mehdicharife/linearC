#ifndef NOMINAL_DATA_TYPE_H
#define NOMINAL_DATA_TYPE_H

#include <stddef.h>

typedef struct nominal_data_type nominal_data_type;

int nominal_data_type_cmp(nominal_data_type* ptr1, nominal_data_type* ptr2);

struct nominal_data_type {
    char* (*get_val)(nominal_data_type* pthis);
    int (*compare_to)(nominal_data_type* pthis, nominal_data_type* pother);
};


#endif

