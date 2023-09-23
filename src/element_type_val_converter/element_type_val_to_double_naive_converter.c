#include "../../include/element_type_val_to_double_converter.h"
#include "../../include/element_type_val_to_double_naive_converter.h"
#include <stdlib.h>
#include <stdio.h>

element_type_val_to_double_converter* new_element_type_val_to_double_naive_converter() {
    static element_type_val_to_double_converter* ret = NULL;
    if(ret == NULL) {
        element_type_val_to_double_converter* ret = malloc(sizeof(element_type_val_to_double_converter*));

        ret->parent.visit_int = element_type_to_double_naive_converter_visit_int_element_type;
        ret->parent.visit_double = element_type_to_double_naive_converter_visit_double_element_type;
        ret->parent.visit_string = element_type_to_double_naive_converter_visit_string_element_type;
    }

    return ret;
}

void element_type_to_double_naive_converter_visit_int_element_type(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_val_to_double_converter* pconverter = (element_type_val_to_double_converter*) pvisitor;
    void* input = pconverter->input;
    pconverter->conversion = (double) *((int*) input);
}

void element_type_to_double_naive_converter_visit_string_element_type(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_val_to_double_converter* pconverter = (element_type_val_to_double_converter*) pvisitor;
    sscanf(*((char**) pconverter->input), "%lf", &(pconverter->conversion));
}

void element_type_to_double_naive_converter_visit_double_element_type(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_val_to_double_converter* pconverter = (element_type_val_to_double_converter*) pvisitor;
    pconverter->conversion = (double) *((double*) pconverter->input);
}