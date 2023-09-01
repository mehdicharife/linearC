#include "../../include/uniform_type_distribution.h"
#include <stdlib.h>

type_distribution* new_uniform_type_distribution(element_type* ptype) {
    uniform_type_distribution* pdistr = (uniform_type_distribution*) malloc(sizeof(uniform_type_distribution));
    pdistr->ptype = ptype;

    pdistr->parent.get_cell_type = uniform_type_distribution_get_cell_type;
    pdistr->parent.get_type_count = uniform_type_distribution_get_type_count;
    pdistr->parent.total_size_before = uniform_type_distribution_total_size_before;
    pdistr->parent.get_kind = uniform_type_distribution_get_kind;
    pdistr->parent.equals = uniform_type_distribution_equals;
    pdistr->parent.all_types_are_addable = uniform_type_distribution_all_types_are_addable;

    return (type_distribution*) pdistr;
}


element_type* uniform_type_distribution_get_cell_type(type_distribution* pdistr, size_t row, size_t col) {
    return ((uniform_type_distribution*) pdistr)->ptype;
}

size_t uniform_type_distribution_total_size_before(type_distribution* pdistr, size_t row_count, size_t col_count, spatial_order* porder, size_t row_id, size_t col_id) {
    size_t element_size = ((uniform_type_distribution*) pdistr)->ptype->size;
    size_t element_count;

    switch(porder->first_track) {
        case row:
            element_count = row_id*col_count + col_id;
            break;

        case col:
            element_count = col_id*row_count + row_id;
            break;
    }

    return element_count*element_size;
}

type_distribution_kind uniform_type_distribution_get_kind(void) {
    return uniform;
}

bool uniform_type_distribution_equals(type_distribution* pthis, type_distribution* pother) {
    if(pthis->get_kind() != pother->get_kind()) {
        return false;
    }
    
    uniform_type_distribution* pdistr1 = (uniform_type_distribution*) pthis;
    uniform_type_distribution* pdistr2 = (uniform_type_distribution*) pother;

    return (pdistr1->ptype == pdistr2->ptype);
}

bool uniform_type_distribution_all_types_are_addable(type_distribution* pthis) {
    uniform_type_distribution* pdistr = (uniform_type_distribution*) pthis;
    if(pdistr->ptype->add == NULL) {
        return false;
    }

    return true;
}

size_t uniform_type_distribution_get_type_count(type_distribution* pdsitr) {
    return 1;
}

