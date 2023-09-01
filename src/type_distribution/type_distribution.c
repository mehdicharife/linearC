#include "../../include/type_distribution.h"
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