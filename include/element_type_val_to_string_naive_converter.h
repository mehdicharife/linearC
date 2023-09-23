#ifndef ELEMENT_TYPE_VAL_TO_STRING_NAIVE_CONVERTER_H
#define ELEMENT_TYPE_VAL_TO_STRING_NAIVE_CONVERTER_H

#include "element_type_val_to_string_converter.h"


element_type_val_to_string_converter* new_element_type_val_to_string_naive_converter();

void element_type_val_to_string_naive_converter_visit_double_element_type(element_type_visitor* pvisitor, element_type* ptype);
void element_type_val_to_string_naive_converter_visit_int_element_type(element_type_visitor* pvisitor, element_type* ptype);
void element_type_val_to_string_naive_converter_visit_string_element_type(element_type_visitor* pvisitor, element_type* ptype);

#endif