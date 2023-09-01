#ifndef TYPE_PER_TRACK_DISTRIBUTION_H

#define TYPE_PER_TRACK_DISTRIBUTION_H

#include "type_distribution.h"

typedef struct type_per_track_distribution type_per_track_distribution;

struct type_per_track_distribution {
    type_distribution parent;
    track_kind tkind;
    element_type* types;
    size_t type_count;
};

type_distribution* new_type_per_track_distribution(element_type* types, size_t type_count);
element_type* type_per_track_distribution_get_cell_type(type_distribution* pdistr, size_t row, size_t col);
size_t type_per_track_distribution_get_sub_track_size(type_distribution* pdistr, size_t row_count, size_t col_count, track_kind tkind, size_t track_id, size_t start_track, size_t end_track);
size_t type_per_track_distribution_total_size_before(type_distribution* pdsitr, size_t row_count, size_t col_count, spatial_order* porder, size_t row, size_t col);
size_t type_per_track_distribution_get_type_count(type_distribution* pdistr);
type_distribution_kind type_per_track_distribution_get_kind(void);
bool type_per_track_distribution_equals(type_distribution* pdistr1, type_distribution* pdistr2);
bool type_per_track_distribution_all_types_are_addable(type_distribution* pdistr);


#endif