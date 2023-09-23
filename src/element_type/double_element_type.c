#include "../../include/double_element_type.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

element_type* new_double_element_type() {
    static element_type* ptype = NULL;

    if(ptype == NULL) {
        ptype = (element_type*) malloc(sizeof(element_type));

        ptype->size = sizeof(double);
        ptype->name = "double";
        ptype->pointer_addition = double_element_type_pointer_addition;
        ptype->add = double_element_type_add;
        ptype->subtract = double_element_type_substract;
        ptype->are_equal = double_element_type_are_equal;
        ptype->get_addition_identity = double_element_type_get_addition_identity;
        ptype->multiply = double_element_type_multiply;
        ptype->set = double_element_type_set;
        ptype->matches_string = double_element_type_matches_string;
        ptype->get_from_string = double_element_type_get_from_string;
        ptype->print = double_element_type_print;
        ptype->accept = double_element_type_accept;
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

void double_element_type_substract(void* pd1, void* pd2, void* output) {
    *((double*) output) = *((double*) pd1) - *((double*) pd2);
    return;
}

void double_element_type_set(void* tobesetted, void* pvalue) {
    *((double*) tobesetted) = *((double*) pvalue);
    return;
}

void* double_element_type_get_addition_identity() {
    double* pzero = (double*) malloc(sizeof(double));
    *pzero = 0;
    
    return (void*) pzero;
}

void* double_element_type_multiply(void* px, void* py) {
    double* ret = (double*) malloc(sizeof(double));

    *ret = (*((double*) px)) * (*((double*) py));

    return ret;
}

bool double_element_type_are_equal(void* px, void* py) {
    return labs(*((double*) px) - *((double*) py)) < 0.00001;
}

bool double_element_type_matches_string(char* str) {
    bool dotted = false;
    bool digits_after_dot = false;

    for(size_t k = 0; k < strlen(str); k++) {
        if(!isdigit(str[k])) {
            if(str[k] == '.') {
                dotted = true;
                continue;
            }
            if(k == 0 && str[k] == '-') { continue; }
            return false;
        }

        if(dotted && !digits_after_dot) {
            digits_after_dot = true;
        }

    }

    return dotted && digits_after_dot;
}

// consider handling cases like "\"1.23\""
void* double_element_type_get_from_string(char* str) {
    double* px = malloc(sizeof(double));
    sscanf(str, "%lf", px);
    return (void*) px;
}


void double_element_type_print(void* pelement) {
    printf("%lf\n",  *((double*) pelement));
}


void double_element_type_accept(element_type* ptype, element_type_visitor* pvisitor) {
    pvisitor->visit_double(pvisitor, ptype);
}