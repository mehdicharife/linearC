#ifndef DOUBLE_BASED_CONTINUOUS_DATA_TYPE_H
#define DOUBLE_BASED_CONTINUOUS_DATA_TYPE_H

#include "continuous_data_type.h"

struct double_based_continuous_data_type {
    continuous_data_type parent;
    double val;
};


continuous_data_type* new_double_based_continuous_data_type(double x);


#endif