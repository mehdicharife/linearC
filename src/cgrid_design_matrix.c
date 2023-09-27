#include "../include/design_matrix.h"
#include "../include/cgrid_design_matrix.h"
#include "../include/double_based_continuous_data_type.h"
#include "../include/uint_based_count_data_type.h"
#include "../include/string_based_nominal_data_type.h"
#include "../include/element_type_val_to_double_naive_converter.h"
#include "../include/element_type_val_to_int_naive_converter.h"
#include "../include/element_type_val_to_string_naive_converter.h"



size_t get_statistical_data_type_count(cgrid_design_matrix* pmatrix, statistical_data_type type);

//If you have a function that accepts an argument of a certain type, and you assert a certain condition on that argument at the start of
// the function, consider creating a subtype that corresponds to the expectation of your function
design_matrix* new_cgrid_design_matrix(matrix* pmatrix, element_type_to_statistical_type_mapper* pmapper) {
    cgrid_design_matrix* ret = malloc(sizeof(cgrid_design_matrix));
    ret->pgrid = pmatrix;
    ret->pmapper = pmapper;

    ret->pto_double_converter = new_element_type_val_to_double_naive_converter();
    ret->pto_int_converter = new_element_type_val_to_int_naive_converter();
    ret->pto_string_converter = new_element_type_val_to_string_naive_converter();

    size_t col_count = (pmatrix == NULL) ? 0 : pmatrix->col_count;
    ret->statistical_types = malloc(sizeof(statistical_data_type)*col_count);
    for(size_t k = 0; k < col_count; k++) {
        ret->statistical_types[k] = undefined;
    }
     
    ret->parent.get_val_of_continuous_feature = cgrid_design_matrix_get_val_of_continuous_feature;
    ret->parent.get_val_of_count_feature = cgrid_design_matrix_get_val_of_count_feature;
    ret->parent.get_val_of_nominal_feature = cgrid_design_matrix_get_val_of_nominal_feature;

    ret->parent.continuous_features_count = get_statistical_data_type_count(ret, continuous);
    ret->parent.count_features_count = get_statistical_data_type_count(ret, count);
    ret->parent.nominal_features_count = get_statistical_data_type_count(ret, nominal);
    ret->parent.ordinal_features_count = get_statistical_data_type_count(ret, ordinal);

    return (design_matrix*) ret;
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
    
    int element_type_val = get_element_type_val_as_int(pval, ptype, pmatrix->pto_int_converter);

    
    return new_uint_based_count_data_type(element_type_val);
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

        if(get_statistical_data_type_from_element_type(get_cell_type(pmatrix->pgrid, 0, k), pmatrix->pmapper) == ptype) {
            count++;
        }

        if(count == j) {
            return k;
        }
    }

    return -1;
}

size_t get_statistical_data_type_count(cgrid_design_matrix* pmatrix, statistical_data_type type) {
    for(size_t k = 0; k < pmatrix->pgrid->col_count; k++) {
        if(get_jth_statistical_feature_index_of_type(pmatrix, type, k) == -1) {
            return k;
        }
    }

    return pmatrix->pgrid->col_count;
    
}


void set_feature_type_and_order_based_on_col_index(cgrid_design_matrix* pmatrix, size_t col, statistical_data_type* ptype, size_t* porder) {

    size_t ft_types_count = 4;
    size_t ft_counts[] = {pmatrix->parent.continuous_features_count, 
                          pmatrix->parent.count_features_count, 
                          pmatrix->parent.ordinal_features_count,
                          pmatrix->parent.nominal_features_count
    };
    statistical_data_type ft_types[] = {continuous, count, ordinal, nominal};

    for(size_t ft_type_index = 0; ft_type_index < ft_types_count; ft_type_index++) {
        for(size_t ft_index = 0; ft_index < ft_counts[ft_type_index]; ft_index++) {
            if(get_jth_statistical_feature_index_of_type(pmatrix, ft_types[ft_type_index], ft_index) == col) {
                *porder = ft_index;
                *ptype = ft_types[ft_type_index];
                return;
            }
        }
    }
}


statistical_data_type get_statistical_data_type_of_col(cgrid_design_matrix* pmatrix, size_t col_index) {
    if(pmatrix->statistical_types[col_index] != undefined) {
        return pmatrix->statistical_types[col_index];
    }

    matrix* cgrid = pmatrix->pgrid;
    element_type* ptype = get_cell_type(cgrid, 0, col_index);//
    element_type_to_statistical_type_mapper* pmapper = pmatrix->pmapper;

    return get_statistical_data_type_from_element_type(ptype, pmapper);//
}