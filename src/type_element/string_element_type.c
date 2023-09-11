#include "../../include/string_element_type.h"
#include "../../include/double_element_type.h"
#include "../../include/int_element_type.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

element_type* new_string_element_type() {
    static element_type* ptype = NULL;

    if(ptype == NULL) {
        ptype = (element_type*) malloc(sizeof(element_type));

        ptype->size = sizeof(char*);
        ptype->name = "string";
        ptype->pointer_addition = string_element_type_pointer_addition;
        ptype->set = string_element_type_set;
        ptype->are_equal = string_element_type_are_equal;
        ptype->get_addition_identity = string_element_type_get_addition_identity;
        ptype->matches_string = string_element_type_matches_string;
        ptype->get_from_string = string_element_type_get_from_string;
        ptype->print = string_element_type_print;

        ptype->add = NULL;
        ptype->subtract = NULL;
        ptype->multiply = NULL;
    }

    return ptype;
}

void* string_element_type_pointer_addition(void* ptr, size_t offset) {
    return (void*) (((char**) ptr) + offset);
}


void string_element_type_set(void* tobesetted, void* pvalue) {
    assert(tobesetted != NULL && pvalue != NULL);
    char** pdestination = tobesetted;
    char** psource = pvalue;
    *pdestination = malloc(strlen(*psource));
    strcpy(*pdestination, *psource);
}



void* string_element_type_get_addition_identity() {
    char** pidentity= malloc(sizeof(char*));
    *pidentity = strdup("");
    
    return (void*) pidentity;
}


bool string_element_type_are_equal(void* pstr1, void* pstr2) {
    return !strcmp(*((char**) pstr1), *((char**) pstr2));
}



bool string_element_type_matches_string(char* str) {
    element_type* pdbl = new_double_element_type();
    element_type* pint = new_int_element_type();

    return !(pdbl->matches_string(str)) && !(pint->matches_string(str)); 
}

void* string_element_type_get_from_string(char* str) {
    assert(str != NULL);

    char** ret = malloc(sizeof(char**));
    *ret = malloc(strlen(str) + 1); 
    sscanf(str, "%s", *ret);
    return (void*) ret;
}


void string_element_type_print(void* pelement) {
    printf("%s\n",  *((char**) pelement));
}

