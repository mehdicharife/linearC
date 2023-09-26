#include "../include/double_based_continuous_data_type.h"
#include <stdlib.h>


continuous_data_type* new_double_based_continuous_data_type(double x) {
    double_based_continuous_data_type* ret = malloc(sizeof(double_based_continuous_data_type));
    ret->val = x;
    ret->parent.compare_to = double_based_continuous_data_type_compare_to;

    return (continuous_data_type*) ret;
}

double double_based_continuous_data_type_compare_to(continuous_data_type* ptr1, continuous_data_type* ptr2) {
    double_based_continuous_data_type* cptr1 = (double_based_continuous_data_type*) ptr1;
    double_based_continuous_data_type* cptr2 = (double_based_continuous_data_type*) ptr2;
    
    return cptr1->val - cptr2->val;
}