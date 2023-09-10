#include "../include/int_element_type.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

element_type* new_int_element_type() {
    static element_type* ptype = NULL;

    if(ptype == NULL) {
        ptype = (element_type*) malloc(sizeof(element_type));

        ptype->size = sizeof(int);
        ptype->name = "int";
        ptype->pointer_addition = int_element_type_pointer_addition;
        ptype->add = int_element_type_add;
        ptype->subtract = int_element_type_substract;
        ptype->are_equal = int_element_type_are_equal;
        ptype->get_addition_identity = int_element_type_get_addition_identity;
        ptype->multiply = int_element_type_multiply;
        ptype->set = int_element_type_set;
        ptype->matches_string = int_element_type_matches_string;
        ptype->get_from_string = int_element_type_get_from_string;
        ptype->print = int_element_type_print;
    }

    return ptype;
}

void* int_element_type_pointer_addition(void* ptr, size_t offset) {
    return (void*) (((int*) ptr) + offset);
}

void int_element_type_add(void* pd1, void* pd2, void* output) {
    *((int*) output) = *((int*) pd1) + *((int*) pd2);
    return;
}

void int_element_type_substract(void* pd1, void* pd2, void* output) {
    *((int*) output) = *((int*) pd1) - *((int*) pd2);
    return;
}

void int_element_type_set(void* tobesetted, void* pvalue) {
    *((int*) tobesetted) = *((int*) pvalue);
    return;
}

void* int_element_type_get_addition_identity() {
    int* pzero = (int*) malloc(sizeof(int));
    *pzero = 0;
    
    return (void*) pzero;
}

void* int_element_type_multiply(void* px, void* py) {
    int* ret = (int*) malloc(sizeof(int));

    *ret = (*((int*) px)) * (*((int*) py));

    return ret;
}

bool int_element_type_are_equal(void* px, void* py) {
    return *((int*) px) == *((int*) py);
}

bool int_element_type_matches_string(char* str) {
    if(str[0] == '0') {
        return (strlen(str) == 1);
    }

    for(size_t k = 0; k < strlen(str); k++) {
        if(!isdigit(str[k])) {
            return false;
        }

    }

    return true;
}

void* int_element_type_get_from_string(char* str) {
    int* pk = malloc(sizeof(int));
    sscanf(str, "%d", pk);
    return (void*) pk;
}

void int_element_type_print(void* pelement) {
    printf("%d\n", *((int*) pelement));
}