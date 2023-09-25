#ifndef CONTINUOUS_DATA_TYPE_H
#define CONTINUOUS_DATA_TYPE_H

#include <stddef.h>

typedef struct continuous_data_type continuous_data_type;



struct continuous_data_type {
    /* tell don't ask
    double (*get_value)(continuous_data_type* pthis);
    void (*set_value_to)(continuous_data_type* pthis, double val);*/ 
    double (*compare_to)(continuous_data_type* pthis, continuous_data_type* pother);
};


#endif

