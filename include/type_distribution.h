#ifndef TYPE_DISTRIBUTION_H
    #define TYPE_DISTRIBUTION_H

    #include "element_type.h"
    #include <stdbool.h>

    
    typedef struct type_distribution type_distribution;
    typedef enum track_kind track_kind;
    typedef struct spatial_order spatial_order;
    typedef enum type_distribution_kind type_distribution_kind;
    

    enum type_distribution_kind {
        uniform,
        type_per_track
    };

    enum track_kind {
        row,
        col
    };

    struct spatial_order {
        track_kind first_track;
        track_kind second_track;
    };
    
    spatial_order* colexcographical();
    spatial_order* lexicographical();


    struct type_distribution {
        element_type* (*get_cell_type)(type_distribution* pthis, size_t row, size_t col);
        size_t (*total_size_before)(type_distribution* pthis, size_t row_count, size_t col_count, spatial_order* porder, size_t row, size_t col);
        size_t (*get_sub_track_size)(type_distribution* pthis, size_t row_count, size_t col_count, track_kind kind, size_t track_index, size_t start_track, size_t finish_track);
        size_t (*get_type_count)(type_distribution* pthis);
        bool (*all_types_are_addable)(type_distribution* pthis);

        type_distribution_kind (*get_kind)(void);
        bool (*equals)(type_distribution* pthis, type_distribution* pother);
    };

    size_t get_track_size(type_distribution* pdistr, size_t row_count, size_t col_count, track_kind tkind, size_t track_id);
    size_t get_row_size(type_distribution* pdistr, size_t row_count, size_t col_count, size_t row_id);
    size_t get_col_size(type_distribution* pdistr, size_t row_count, size_t col_count, size_t col_id);

    size_t get_sub_track_size(type_distribution* pdistr, size_t row_count, size_t col_count, track_kind tkind, size_t track_id, size_t start_track, size_t finish_track);





#endif