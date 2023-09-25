#include "../../include/type_distribution.h"
#include "../../include/uniform_type_distribution.h"
#include "../../include/type_per_track_distribution.h"
#include <stdlib.h>



size_t get_sub_track_size(type_distribution* pdistr, size_t row_count, size_t col_count, track_kind tkind, size_t track_id, size_t start, size_t end) {
    return pdistr->get_sub_track_size(pdistr, row_count, col_count, tkind, track_id, start, end);
}

size_t get_track_size(type_distribution* pdistr, size_t row_count, size_t col_count, track_kind tkind, size_t track_id) {
    size_t end = (tkind == row) ? col_count : row_count;
    return get_sub_track_size(pdistr, row_count, col_count, tkind, track_id, 0, end);
}

spatial_order* lexicographical() {
    static spatial_order* porder = NULL;
    if(porder == NULL) {
        porder = malloc(sizeof(spatial_order));
        porder->first_track = row;
        porder->second_track = col;
    }

    return porder;
}


spatial_order* colexcographical() {
    static spatial_order* porder = NULL;
    if(porder == NULL) {
        porder = malloc(sizeof(spatial_order));
        porder->first_track = col;
        porder->second_track = row;
    }

    return porder;
}


type_distribution* new_type_distribution_from_types_array(element_type** array, size_t type_count) {
    bool is_uniform = true;

    for(size_t k = 0; k < type_count - 1; k++) {
        if(array[k] != array[k + 1]) { is_uniform = false; break;} 
    }

    

    if(is_uniform) {

        return new_uniform_type_distribution(array[0]);
    }

    

    return new_type_per_track_distribution(col, array, type_count);
}



type_distribution* new_type_distribution_from_csv_file(FILE* fp) {
    size_t type_count;
    element_type** types;
    set_element_types_from_csv_file(&types, &type_count, fp);

    

    return new_type_distribution_from_types_array(types, type_count);
}