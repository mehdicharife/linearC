#include "../include/element_type_comparator.h"
#include <string.h>
#include <stdio.h>
#include "../include/utils.h"


int element_type_cmpr_eloquence(element_type* ptype1, element_type* ptype2) {
    char* ordered_names[] = {"string", "double", "float", "int"};
    
    int k1 = get_str_index(ordered_names, 4, ptype1->name);
    int k2 = get_str_index(ordered_names, 4, ptype2->name);

    return k2 - k1;
}