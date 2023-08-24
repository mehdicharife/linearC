#include "double_element_type.h"
#include <stdlib.h>

element_type* new_double_element_type() {
    static element_type* ptype = NULL;

    if(ptype == NULL) {
        ptype = (element_type*) malloc(sizeof(element_type));

        ptype->size = sizeof(double);
        ptype->pointer_addition = double_element_type_pointer_addition;
        ptype->add = double_element_type_add;
        ptype->get_addition_identity = double_element_type_get_addition_identity;
        ptype->multiply = double_element_type_multiply;
        ptype->set = double_element_type_set;
    }

    return ptype;
}

void* double_element_type_pointer_addition(void* ptr, size_t offset) {
    return (void*) (((double*) ptr) + offset);
}

void double_element_type_add(void* pd1, void* pd2, void* output) {
    *((double*) output) = *((double*) pd1) + *((double*) pd2);
    return;
}

void double_element_type_set(void* tobesetted, void* pvalue) {
    *((double*) tobesetted) = *((double*) pvalue);
    return;
}

void* double_element_type_get_addition_identity() {
    static double* pzero = NULL;
    if(pzero == NULL) {
        pzero = (double*) malloc(sizeof(double));
        *pzero = 0;
    }

    return (void*) pzero;
}

void* double_element_type_multiply(void* px, void* py) {
    double* ret = (double*) malloc(sizeof(double));

    *ret = (*((double*) px)) * (*((double*) py));

    return ret;
}