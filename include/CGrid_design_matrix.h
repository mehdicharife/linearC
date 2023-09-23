#ifndef CGRID_DESIGN_MATRIX_H
#define CGRID_DESIGN_MATRIX_H

#include "design_matrix.h"
#include "matrix.h"
#include "element_type_to_statistical_type_mapper.h"

typedef struct CGrid_design_matrix CGrid_design_matrix;

struct CGrid_design_matrix {
    design_matrix parent;
    matrix* pgrid;
    element_type_to_statistical_type_mapper* pmapper;
    
    statistical_data_type* feature_types;
};

design_matrix* new_CGrid_design_matrix(matrix* pmatrix, element_type_to_statistical_type_mapper* pmapper, statistical_data_type* ft_types);
datum* CGrid_design_matrix_get_data_point(design_matrix* pthis, size_t x, size_t y);
statistical_data_type CGrid_design_matrix_get_feature_type(design_matrix* pthis, size_t y);
size_t CGrid_design_matrix_get_features_count(design_matrix* pthis);
size_t CGrid_design_matrix_get_points_count(design_matrix* pthis);

statistical_data_type get_statistical_data_type_from_element_type(element_type* ptype);

#endif