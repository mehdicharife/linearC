#ifndef UNIFORM_TYPE_DISTRIBUTION

    #define UNIFORM_TYPE_DISTRIBUTION


    #include "type_distribution.h"

    typedef struct uniform_type_distribution uniform_type_distribution;

    struct uniform_type_distribution {
        type_distribution parent;
        element_type* ptype;
    };

    type_distribution*  new_uniform_type_distribution(element_type* ptype);
    element_type* uniform_type_distribution_get_cell_type(type_distribution* pthis, size_t row_count, size_t col_count, size_t row, size_t col);
    size_t uniform_type_distribution_total_size_before(type_distribution* pthis, size_t row_count, size_t col_count, spatial_order order, size_t row, size_t col);
    type_distribution_kind uniform_type_distribution_get_kind(void);
    bool uniform_type_distribution_equals(type_distribution* pthis, type_distribution* pother);
    bool uniform_type_distribution_all_types_are_addable(type_distribution* pthis);
    size_t uniform_type_distribution_get_type_count(type_distribution* pthis);


#endif