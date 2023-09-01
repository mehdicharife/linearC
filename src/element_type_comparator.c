#include "../include/element_type_comparator.h"

int element_type_cmpr_eloquence(element_type* ptype1, element_type* ptype2) {
    if(ptype1->name == ptype2->name) {
        return 0;
    }

    return 2;
}