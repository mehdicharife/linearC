#include <gtest/gtest.h>

extern "C" {
    #include "double_element_type.c"
    #include "type_distribution/uniform_type_distribution.c"
    #include "storage/row_major_storage.c"
    #include "matrix.c"
}


TEST(row_major_double_matrix_test_suite, sets_a_cell) {
    double x = 5.0;
    double y = 8.0;

    size_t row_count = 3, col_count = 2;

    matrix* pmatrix = new_row_major_double_matrix();
    allocate_storage(pmatrix, row_count, col_count);


    set_cell(pmatrix, 0, 0, &x);
    EXPECT_EQ( *((double*) get_cell_address(pmatrix, 0, 0)), x);

    set_cell(pmatrix, 1, 1, &y);
    EXPECT_EQ( *((double*) get_cell_address(pmatrix, 1, 1)), y);
    
}



TEST(row_major_double_matrix_test_suite, sets_all_cells) {
    double x = 8;
    size_t row_count = 8, col_count = 2;

    matrix* pmatrix = new_row_major_double_matrix();
    allocate_storage(pmatrix, row_count, col_count);
    set_all_cells(pmatrix, &x);

    
    int failures_count = 0;
    for(size_t row = 0; row < pmatrix->row_count; row++) {
        for(size_t col = 0; col < pmatrix->col_count; col++) {
            //printf("%f\n", *((double*) get_cell_address(pmatrix, row, col)));
            EXPECT_EQ(*((double*) get_cell_address(pmatrix, row, col)),
                        x 
            );
        }
    }

}



TEST(row_major_double_matrix_test_suite, adds_two_matrices) {
    double a = 1, b = 2;

    matrix* pA = new_row_major_double_matrix();
    matrix* pB = new_row_major_double_matrix();
    allocate_storage(pA, 2, 2);
    allocate_storage(pB, 2, 2);
    set_all_cells(pA, &a);
    set_all_cells(pB, &b);


    matrix* pC = add_matrices(pA, pB);

    for(size_t row = 0; row < pA->row_count; row++) {
        for(size_t col = 0; col < pA->col_count; col++) {
            EXPECT_EQ(
                *((double*) get_cell_address(pC, row, col)),
                *((double*) get_cell_address(pA, row, col)) + *((double*) get_cell_address(pB, row, col))
            );
        }
    }



}



/*
TEST(row_major_double_matrix_test_suite, multiplies_two_matrices) {
    double a = 3.0, b = 2.0;

    matrix* pA = new_monotype_matrix(new_double_element_type());
    matrix* pB = new_monotype_matrix(new_double_element_type());
    init_monotype_matrix(pA, 2, 3);
    init_monotype_matrix(pB, 3, 2);
    set_monotype_matrix(pA, &a);
    set_monotype_matrix(pB, &b);

    matrix* pC = multiply_monotype_matrices(pA, pB);

    element_type* ptype = ((monotype_matrix*) pC)->ptype;
    void* identity = ptype->get_addition_identity();
    for(size_t row = 0; row < pC->row_count; row++) {
        for(size_t col = 0; col < pC->col_count; col++) {
            void* pexpected =  malloc(sizeof(ptype->size));
            ptype->set(pexpected, identity);

            for(size_t k = 0; k < pA->col_count; k++) {
                void* temp = ptype->multiply(get_cell_address(pA, row, k), 
                                             get_cell_address(pB, k, col)
                );

                ptype->add(pexpected, temp, pexpected);
                free(temp);
            }

            EXPECT_EQ(
                *((double*) pexpected),
                *((double*) get_cell_address(pC, row, col)) 
            );

            free(pexpected);
        }
    }
}
*/