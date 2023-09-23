#include "../../include/element_type_val_to_string_naive_converter.h"
#include <stdlib.h>
#include <stdio.h>

element_type_val_to_string_converter* new_element_type_val_to_string_naive_converter_custom_malloc(void*(*my_malloc)(size_t));

element_type_val_to_string_converter* new_element_type_val_to_string_naive_converter() {
    return new_element_type_val_to_string_naive_converter_custom_malloc(malloc);
}

// the use of a custom malloc is due to the fact that the Criterion testing framework requires using their own cr_malloc when
// parameterizing tests
element_type_val_to_string_converter* new_element_type_val_to_string_naive_converter_custom_malloc(void*(*my_malloc)(size_t)) {
    static element_type_val_to_string_converter* ret = NULL;
    if(ret == NULL) {
        ret = my_malloc(sizeof(element_type_val_to_string_converter));

        ret->my_malloc = my_malloc;
        ret->parent.visit_double = element_type_val_to_string_naive_converter_visit_double_element_type;
        ret->parent.visit_int = element_type_val_to_string_naive_converter_visit_int_element_type;
        ret->parent.visit_string = element_type_val_to_string_naive_converter_visit_string_element_type;
    }

    return (element_type_val_to_string_converter*) ret;
}

void element_type_val_to_string_naive_converter_visit_double_element_type(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_val_to_string_converter* pconverter = (element_type_val_to_string_converter*) pvisitor;
    size_t length = snprintf(NULL, 0, "%lf", *((double*) pconverter->input));
    pconverter->conversion = pconverter->my_malloc(length + 1);
    sprintf(pconverter->conversion, "%lf", *((double*) pconverter->input));
}

void element_type_val_to_string_naive_converter_visit_int_element_type(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_val_to_string_converter* pconverter = (element_type_val_to_string_converter*) pvisitor;
    int input = *((int*) pconverter->input);
    size_t length = snprintf(NULL, 0, "%d", input);
    pconverter->conversion = pconverter->my_malloc(length + 1);
    sprintf(pconverter->conversion, "%d", input);
}

void element_type_val_to_string_naive_converter_visit_string_element_type(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_val_to_string_converter* pconverter = (element_type_val_to_string_converter*) pvisitor;
    pconverter->conversion = pconverter->input;
}