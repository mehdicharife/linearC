#include "../../include/type_per_track_distribution.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>


type_distribution* new_type_per_track_distribution(track_kind tkind, element_type** types, size_t type_count) {
    type_per_track_distribution* pdistr =  malloc(sizeof(type_per_track_distribution));
    pdistr->tkind = tkind;
    pdistr->types = types;
    pdistr->type_count = type_count;

    pdistr->parent.get_cell_type = type_per_track_distribution_get_cell_type;
    pdistr->parent.get_sub_track_size = type_per_track_distribution_get_sub_track_size;
    pdistr->parent.total_size_before = type_per_track_distribution_total_size_before;
    pdistr->parent.get_type_count = type_per_track_distribution_get_type_count;
    pdistr->parent.get_kind = type_per_track_distribution_get_kind;
    pdistr->parent.equals = type_per_track_distribution_equals;
    pdistr->parent.all_types_are_addable = type_per_track_distribution_all_types_are_addable;

    return (type_distribution*) pdistr;
}

element_type* type_per_track_distribution_get_cell_type(type_distribution* pdistr, size_t row, size_t col) {
    type_per_track_distribution* pdistro = (type_per_track_distribution*) pdistr;

    if(pdistro->type_count < col) {
        return NULL;
    }

    return *(pdistro->types + col);
}


size_t type_per_track_distribution_total_size_before(type_distribution* pdistr, size_t row_count, size_t col_count, spatial_order* porder, size_t row_i, size_t col_i) {

    
    size_t main_track_size = get_track_size(pdistr, row_count, col_count, porder->first_track, 0);
    size_t main_track_count = (porder->first_track == row) ? row_i : col_i;
    size_t secondary_track_index = (porder->first_track == row) ? col_i : row_i;
    size_t remainder_size = get_sub_track_size(pdistr, row_count, col_count, porder->first_track, main_track_count, 0, secondary_track_index);

    

    return main_track_count*main_track_size + remainder_size;
}


size_t type_per_track_distribution_get_sub_track_size(type_distribution* pdistr, size_t row_count, size_t col_count, track_kind tkind, size_t track_id, size_t start, size_t end) {

    //printf("haaaaaaaaa\n");
    size_t ret_size;
    type_per_track_distribution* pdistribution = (type_per_track_distribution*) pdistr;
    size_t secondary_track_count = (end - start + 1);

    if(tkind == pdistribution->tkind) {
        ret_size = (pdistribution->types[track_id]->size)*secondary_track_count;
    } else {
        ret_size = 0;
        for(size_t k = start; k < end; k++) {
            ret_size += pdistribution->types[k]->size;
        }   
    }

    return ret_size;
}


size_t type_per_track_distribution_get_type_count(type_distribution* pdistr) {
    return ((type_per_track_distribution*) pdistr)->type_count;
}


bool type_per_track_distribution_all_types_are_addable(type_distribution* pdistr) {
    type_per_track_distribution* pdistribution = (type_per_track_distribution*) pdistr;
    
    for(size_t k = 0; k < pdistribution->type_count; k++) {
        if(pdistribution->types[k]->add == NULL) {
            return false;
        }
    }

    return true;
}

type_distribution_kind type_per_track_distribution_get_kind() {
    return type_per_track;
}


bool type_per_track_distribution_equals(type_distribution* pdistr1, type_distribution* pdistr2) {
    if(pdistr1 == pdistr2) {
        return true;
    }

    if(pdistr1->get_kind() != pdistr2->get_kind()) {
        return false;
    }

    type_per_track_distribution* pdistribution1 = (type_per_track_distribution*) pdistr1;
    type_per_track_distribution* pdistribution2 = (type_per_track_distribution*) pdistr2;
    if(pdistribution1->tkind != pdistribution2->tkind) {
        return false;
    }

    if(pdistribution1->type_count != pdistribution2->type_count) {
        return false;
    }

    if(pdistribution1->types == pdistribution2->types) {
        return true;
    }

    for(size_t k = 0; k < pdistribution1->type_count; k++) {
        if(pdistribution1->types[k] != pdistribution2->types[k]) {
            return false;
        }
    }

    return true;
}
