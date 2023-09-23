#ifndef ELEMENT_TYPE_VAL_TO_STRING_CONVERTER_H
#define ELEMENT_TYPE_VAL_TO_STRING_CONVERTER_H

#include "element_type_visitor.h"
#include <stddef.h>


typedef struct element_type_val_to_string_converter  element_type_val_to_string_converter;


struct element_type_val_to_string_converter {
    element_type_visitor parent;
    void* input;
    char* conversion;
    void* (*my_malloc)(size_t size);
};

char* get_element_type_val_as_string(void* pval, element_type* ptype, element_type_val_to_string_converter* pconverter);

#endif