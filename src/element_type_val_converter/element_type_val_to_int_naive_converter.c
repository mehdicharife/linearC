#include "../../include/element_type_val_to_int_converter.h"
#include "../../include/element_type_val_to_int_naive_converter.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

element_type_val_to_int_converter* new_element_type_val_to_int_naive_converter() {
    static element_type_val_to_int_converter* ret = NULL;
    if(ret == NULL) {
        ret = malloc(sizeof(element_type_val_to_int_converter));

        ret->parent.visit_int = element_type_to_int_naive_converter_visit_int_element_type;
        ret->parent.visit_double = element_type_to_int_naive_converter_visit_double_element_type;
        ret->parent.visit_string = element_type_to_int_naive_converter_visit_string_element_type;
    }

    return ret;
}

void element_type_to_int_naive_converter_visit_double_element_type(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_val_to_int_converter* pconverter = (element_type_val_to_int_converter*) pvisitor;
    void* input = pconverter->input;
    pconverter->conversion = (int) lround(*((double*) input));
}

void element_type_to_int_naive_converter_visit_string_element_type(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_val_to_int_converter* pconverter = (element_type_val_to_int_converter*) pvisitor;
    sscanf(*((char**) pconverter->input), "%d", &(pconverter->conversion));
}

void element_type_to_int_naive_converter_visit_int_element_type(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_val_to_int_converter* pconverter = (element_type_val_to_int_converter*) pvisitor;
    pconverter->conversion =  *((int*) pconverter->input);
}