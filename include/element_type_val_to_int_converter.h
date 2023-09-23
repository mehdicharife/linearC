#ifndef ELEMENT_TYPE_VAL_TO_INT_CONVERTER_H
#define ELEMENT_TYPE_VAL_TO_INT_CONVERTER_H

#include "element_type_visitor.h"

typedef struct element_type_val_to_int_converter element_type_val_to_int_converter;

struct element_type_val_to_int_converter {
    element_type_visitor parent;
    void* input;
    int conversion;
};

int get_element_type_val_as_int(void* pval, element_type* ptype, element_type_val_to_int_converter* pconverter);

#endif