#include "../include/design_matrix.h"
#include "../include/cgrid_design_matrix.h"
#include "../include/double_based_continuous_data_type.h"
#include "../include/uint_based_count_data_type.h"
#include "../include/string_based_nominal_data_type.h"

//If you have a function that accepts an argument of a certain type, and you assert a certain condition on that argument at the start of
// the function, consider creating a subtype that corresponds to the expectation of your function
cgrid_design_matrix* new_cgrid_design_matrix(matrix* pmatrix, element_type_to_statistical_type_mapper* pmapper) {
    assert(pmatrix->pdistr->get_kind() == uniform || pmatrix->pdistr->get_kind() == type_per_track);

    cgrid_design_matrix* ret = malloc(sizeof(cgrid_design_matrix));
    ret->pgrid = pmatrix;
    ret->pmapper = pmapper;
    ret->statistical_types = malloc(sizeof(statistical_data_type)*pmatrix->col_count);
    for(size_t k = 0; k < pmatrix->col_count; k++) {
        ret->statistical_types[k] = undefined;
    }
     
    ret->parent.get_val_of_continuous_feature = cgrid_design_matrix_get_val_of_continuous_feature;
    ret->parent.get_val_of_count_feature = cgrid_design_matrix_get_val_of_count_feature;
    ret->parent.get_val_of_nominal_feature = cgrid_design_matrix_get_val_of_nominal_feature;

    return ret;
}




continuous_data_type* cgrid_design_matrix_get_val_of_continuous_feature(design_matrix* pdmatrix, size_t sample_index, size_t feature_index) {
    cgrid_design_matrix* pmatrix = (cgrid_design_matrix*) pdmatrix;
    
    size_t col_index = get_jth_statistical_feature_index_of_type(pmatrix, continuous, feature_index);
    
    element_type* ptype = get_cell_type(pmatrix->pgrid, sample_index, col_index);
    void* pval = get_cell_address(pmatrix->pgrid, sample_index, col_index);
    return new_double_based_continuous_data_type(get_element_type_val_as_double(pval, ptype, pmatrix->pto_double_converter));
} 

// add logic that excludes other int-stored types  when going through
count_data_type* cgrid_design_matrix_get_val_of_count_feature(design_matrix* pdmatrix, size_t sample_index, size_t feature_index) {
    cgrid_design_matrix* pmatrix = (cgrid_design_matrix*) pdmatrix;

    size_t col_index = get_jth_statistical_feature_index_of_type(pmatrix, count, feature_index);

    element_type* ptype = get_cell_type(pmatrix->pgrid, sample_index, col_index);
    void* pval = get_cell_address(pmatrix->pgrid, sample_index, col_index);
    return new_uint_based_count_data_type(get_element_type_val_as_int(pval, ptype, pmatrix->pto_int_converter));
}


nominal_data_type* cgrid_design_matrix_get_val_of_nominal_feature(design_matrix* pdmatrix, size_t sample_index, size_t feature_index) {
    cgrid_design_matrix* pmatrix = (cgrid_design_matrix*) pdmatrix;
    size_t col_index = get_jth_statistical_feature_index_of_type(pmatrix, nominal, feature_index);

    element_type* ptype = get_cell_type(pmatrix->pgrid, sample_index, col_index);
    void* pval = get_cell_address(pmatrix->pgrid, sample_index, col_index);
    return new_string_based_nominal_data_type(get_element_type_val_as_string(pval, ptype, pmatrix->pto_string_converter));
}



int get_jth_statistical_feature_index_of_type(cgrid_design_matrix* pmatrix, statistical_data_type ptype, size_t j) {
    size_t count = -1;
    for(size_t k = 0; k < pmatrix->pgrid->col_count; k++) {
        if(pmatrix->statistical_types[k] == ptype) { 
            count++; 
            continue; 
        }

        if(get_statistical_data_type(get_cell_type(pmatrix->pgrid, 0, k), pmatrix->pmapper) == ptype) {
            count++;
        }

        if(count == j) {
            return k;
        }
    }

    return -1;
}