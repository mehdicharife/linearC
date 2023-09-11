#include "../../include/element_type_eloquence_cmp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/utils.h"


element_type* new_least_eloquent() {
    static element_type* lel = NULL;
    if(lel == NULL) {
        lel = malloc(sizeof(element_type*));
    }
    return lel;
}

int element_type_eloquence_cmp(element_type* ptype1, element_type* ptype2) {
    if(ptype1 == ptype2) { return 0;}
    if(ptype1 == new_least_eloquent()) { return -1; }
    if(ptype2 == new_least_eloquent()) { return 1; }

    char* ordered_names[] = {"string", "double", "float", "int"};
    
    int k1 = get_str_index(ordered_names, 4, ptype1->name);
    int k2 = get_str_index(ordered_names, 4, ptype2->name);

    return k2 - k1;
}

element_type* get_most_eloquent_type(element_type* ptype1, element_type* ptype2) {
    if(element_type_eloquence_cmp(ptype1, ptype2) > 0) {
        return ptype1;
    }

    return ptype2;
}

void set_to_least_eloquent(element_type** arr, size_t arr_size) {
    for(size_t k = 0; k < arr_size; k++) {
        arr[k] = new_least_eloquent();
    }
}


