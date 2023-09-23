#ifndef DESIGN_MATRIX_H
#define DESIGN_MATRIX_H

#include <stddef.h>
#include "statistical_data_type.h"
#include "continuous_data_type.h"
#include "matrix.h"
#include "element_type_to_statistical_type_mapper.h"

typedef struct design_matrix design_matrix;



struct design_matrix {
    continuous_data_type* (*get_val_of_continuous_feature)(design_matrix* pthis, size_t sample_index, size_t ft_index);
    size_t continuous_features_count;

    count_data_type* (*get_val_of_count_feature)(design_matrix* pthis, size_t sample_index, size_t ft_index);
    size_t count_features_count;

    ordinal_data_type* (*get_val_of_ordinal_feature)(design_matrix* pthis, size_t sample_index, size_t ft_index);
    size_t ordinal_features_count;

    nominal_data_type* (*get_val_of_nominal_feature)(design_matrix* pthis, size_t sample_index, size_t ft_index);
    size_t nominal_features_count;

    size_t samples_count;
};


#endif












