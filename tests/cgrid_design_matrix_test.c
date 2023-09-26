#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/matrix.h"
#include "../include/row_major_storage.h"
#include "../include/element_type_to_statistical_type_naive_mapper.h"
#include "../include/cgrid_design_matrix.h"

#include "../include/element_type_val_to_double_converter.h"
#include "../include/element_type_val_to_double_naive_converter.h"
#include "../include/element_type_val_to_int_converter.h"
#include "../include/element_type_val_to_int_naive_converter.h"
#include "../include/element_type_val_to_string_converter.h"
#include "../include/element_type_val_to_string_naive_converter.h"

#include "../include/nominal_data_type.h"
#include "../include/string_based_nominal_data_type.h"
#include "../include/uint_based_count_data_type.h"
#include "../include/double_based_continuous_data_type.h"
#include <unistd.h>

void set_feature_type_and_order_based_on_col_index(cgrid_design_matrix* pmatrix, size_t col, statistical_data_type* ptype, size_t* porder);

matrix* pcgrid;
element_type_to_statistical_type_mapper* pmapper;

void setup() {
    storage* pstorage = new_row_major_storage();
    FILE* fp = fopen("/home/mehdi/linearC/tests/subjects/titanic.csv", "r");
    if(fp == NULL) {
        fprintf(stderr, "Couldn't open file");
    }
    pcgrid = new_csv_generated_matrix(fp, pstorage);


    pmapper = new_element_type_to_statistical_type_naive_mapper();
}

TestSuite(cgrid_design_matrix_test_suite, .init=setup);


Test(cgrid_design_matrix_test_suite, sum_of_features_is_col_count) {
    design_matrix* pmatrix = new_cgrid_design_matrix(pcgrid, pmapper);
    size_t expected = pmatrix->continuous_features_count + pmatrix->nominal_features_count + 
                      pmatrix->count_features_count  + pmatrix->ordinal_features_count;

    cr_assert(eq(int, ((cgrid_design_matrix*) pmatrix)->pgrid->col_count, expected));
}



Test(cgrid_design_matrix_test_suite, cells_correspondance) {
    cgrid_design_matrix* pmatrix = (cgrid_design_matrix*) new_cgrid_design_matrix(pcgrid, pmapper);
    for(size_t j = 0; j < pmatrix->pgrid->col_count; j++) {
        
        statistical_data_type type;
        size_t ft_inner_index;
        set_feature_type_and_order_based_on_col_index((cgrid_design_matrix*) pmatrix, j, &type, &ft_inner_index);
        
        for(size_t i = 0; i < pmatrix->pgrid->row_count; i++) {
            
            void* cell_address = get_cell_address(pmatrix->pgrid, i, j);
            element_type* ptype = get_cell_type(pmatrix->pgrid, i, j);
            
            switch(type) {
                case continuous:
                    continuous_data_type* continuous_pgot = pmatrix->parent.get_val_of_continuous_feature(&(pmatrix->parent), i, ft_inner_index);
                    double curr_cell_as_dbl = get_element_type_val_as_double(cell_address, ptype, new_element_type_val_to_double_naive_converter());
                    continuous_data_type* continuous_pexpected = new_double_based_continuous_data_type(curr_cell_as_dbl);
                    cr_assert(eq(dbl, continuous_pgot->compare_to(continuous_pgot, continuous_pexpected), 0));
                    break;
                
                
                case count:
                    
                    count_data_type* count_pgot = pmatrix->parent.get_val_of_count_feature(&(pmatrix->parent), i, ft_inner_index);
                    
                    element_type_val_to_int_converter* to_int_pconverter = new_element_type_val_to_int_naive_converter();
                    
                    to_int_pconverter->input = cell_address;
                    
                    int curr_cell_as_int = get_element_type_val_as_int(cell_address, ptype, to_int_pconverter);
                    count_data_type* count_pexpected = new_uint_based_count_data_type(curr_cell_as_int);

                    int cmp_result = count_pgot->compare_to(count_pgot, count_pexpected);
                    cr_assert(eq(int, cmp_result, 0));
                    break;
                                
                
                case nominal:
                    nominal_data_type* nominal_pgot = pmatrix->parent.get_val_of_nominal_feature(&(pmatrix->parent), i, ft_inner_index);

                   
                    char* curr_cell_as_string = get_element_type_val_as_string(cell_address, ptype, pmatrix->pto_string_converter);
                    
                    nominal_data_type* nominal_pexpected = new_string_based_nominal_data_type(curr_cell_as_string);
                    int comparison_result = nominal_pgot->compare_to(nominal_pgot, nominal_pexpected);
                    //printf("nominal: (%ld, %ld) : %s\n", i, j, curr_cell_as_string);
                    //sleep(1);
                    cr_assert(eq(int, comparison_result, 0));
                    break;
                
                default:
                    continue;
                
            }
            

        }
    }

}









/*
Test(cgrid_design_matrix_test_suite, first_cell_correspondance) {
    design_matrix* pmatrix = new_cgrid_design_matrix(pcgrid, pmapper);
    statistical_data_type type;
    size_t ft_inner_index;
    set_feature_type_and_order_based_on_col_index((cgrid_design_matrix*) pmatrix, 9, &type, &ft_inner_index);

    cr_assert(eq(int, type, continuous));
}
*/