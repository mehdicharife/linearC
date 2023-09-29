#ifndef CGRID_DESIGN_MATRIX_H
#define CGRID_DESIGN_MATRIX_H

#include "matrix.h"
#include "design_matrix.h"
#include "continuous_data_type.h"
#include "count_data_type.h"
#include "element_type_to_statistical_type_mapper.h"
#include "double_element_type.h"
#include "int_element_type.h"
#include "string_element_type.h"
#include "element_type_val_to_double_converter.h"
#include "element_type_val_to_int_converter.h"
#include "element_type_val_to_string_converter.h"


typedef struct cgrid_design_matrix cgrid_design_matrix;

// element type distribution visitor => statistical data type distribution 
struct cgrid_design_matrix {
    design_matrix parent;
    matrix* pgrid;
    element_type_to_statistical_type_mapper* pmapper;
    statistical_data_type* statistical_types;

    element_type_val_to_double_converter* pto_double_converter;
    element_type_val_to_int_converter* pto_int_converter;
    element_type_val_to_string_converter* pto_string_converter;

    statistical_data_type (*get_col_statistical_data_type)(cgrid_design_matrix* pmatrix, size_t col_index);
};

design_matrix* new_cgrid_design_matrix(matrix* pmatrix, element_type_to_statistical_type_mapper* pmapper);
continuous_data_type* cgrid_design_matrix_get_val_of_continuous_feature(design_matrix* pdmatrix, size_t sample_index, size_t feature_index);
count_data_type* cgrid_design_matrix_get_val_of_count_feature(design_matrix* pdmatrix, size_t sample_index, size_t feature_index);
nominal_data_type* cgrid_design_matrix_get_val_of_nominal_feature(design_matrix* pdmatrix, size_t sample_index, size_t feature_index);






#endif