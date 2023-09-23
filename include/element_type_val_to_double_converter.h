#ifndef ELEMENT_TYPE_VAL_TO_DOUBLE_CONVERTER_H
#define ELEMENT_TYPE_VAL_TO_DOUBLE_CONVERTER_H

#include "element_type_visitor.h"

typedef struct element_type_val_to_double_converter element_type_val_to_double_converter;

struct element_type_val_to_double_converter {
    element_type_visitor parent;
    void* input;
    double conversion;
};

double get_element_type_val_as_double(void* pval, element_type* ptype, element_type_val_to_double_converter* pconverter);

#endif