#include "../include/string_based_nominal_data_type.h"
#include <stdlib.h>


nominal_data_type* new_string_based_nominal_data_type(char* str) {
    string_based_nominal_data_type* ret = malloc(sizeof(string_based_nominal_data_type));
    ret->val = str;
    ret->parent.get_val = string_based_nominal_data_type_get_val;
    ret->parent.compare_to = nominal_data_type_cmp;
    return (nominal_data_type*) ret;
}

char* string_based_nominal_data_type_get_val(nominal_data_type* pthis) {
    return ((string_based_nominal_data_type*) pthis)->val; 
}