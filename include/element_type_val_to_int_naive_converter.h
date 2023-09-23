#ifndef ELEMENT_TYPE_VAL_TO_INT_NAIVE_CONVERTER_H
#define ELEMENT_TYPE_VAL_TO_INT_NAIVE_CONVERTER_H

typedef struct element_type_to_int_converter element_type_to_int_converter;
typedef struct element_type_visitor element_type_visitor;
typedef struct element_type element_type;

element_type_val_to_int_converter* new_element_type_val_to_int_naive_converter(void);

void element_type_to_int_naive_converter_visit_double_element_type(element_type_visitor* pvisitor, element_type* ptype);
void element_type_to_int_naive_converter_visit_int_element_type(element_type_visitor* pvisitor, element_type* ptype);
void element_type_to_int_naive_converter_visit_string_element_type(element_type_visitor* pvisitor, element_type* ptype);

#endif