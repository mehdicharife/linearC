#ifndef DOUBLE_BASED_CONTINUOUS_DATA_TYPE_H
#define DOUBLE_BASED_CONTINUOUS_DATA_TYPE_H

#include "continuous_data_type.h"

typedef struct double_based_continuous_data_type double_based_continuous_data_type;

struct double_based_continuous_data_type {
    continuous_data_type parent;
    double val;
};


continuous_data_type* new_double_based_continuous_data_type(double x);
double double_based_continuous_data_type_compare_to(continuous_data_type* pthis, continuous_data_type* pother);

#endif