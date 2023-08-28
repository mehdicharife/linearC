#ifndef TYPE_DISTRIBUTION_H
    #define TYPE_DISTRIBUTION_H

    #include "../element_type.h"
    #include <stdbool.h>

    
    typedef struct type_distribution type_distribution;
    

    enum type_distribution_kind {
        uniform,
        type_per_col,
        type_per_row
    };

    enum spatial_order {
        lexicographical,
        colexicographical
    };
    
    typedef enum spatial_order spatial_order;
    typedef enum type_distribution_kind type_distribution_kind;

    struct type_distribution {
        size_t row_count;
        size_t col_count;
        element_type* (*get_cell_type)(type_distribution* pthis, size_t row, size_t col);
        size_t (*get_type_count)(type_distribution* pthis);
        size_t (*total_size_before)(type_distribution* pthis, size_t row, size_t col, spatial_order order);

        type_distribution_kind (*get_kind)(void);
        bool (*equals)(type_distribution* pthis, type_distribution* pother);
        bool (*all_types_are_addable)(type_distribution* pthis);
    };





#endif