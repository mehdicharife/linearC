#include <gtest/gtest.h>

extern "C" {
    #include "matrix.c"
    #include "monotype_matrix.c"
    #include "double_element_type.c"
}


TEST(monotype_matrix_test_suite, sets_a_cell) {
    double x = 5.0;
    double y = 8.0;

    size_t row_count = 3, col_count = 2;
    size_t row = 1, col = 1;
    element_type* pdouble_type = new_double_element_type();
    matrix* pmatrix = new_monotype_matrix(pdouble_type);
    init_monotype_matrix(pmatrix, row_count, col_count);

    set_cell(pmatrix, row, col, &x);
    set_cell(pmatrix, row_count - 1, col_count - 1, &y);

    EXPECT_EQ( *((double*) get_cell_address(pmatrix, row, col)), x);
    EXPECT_EQ( *((double*) get_cell_address(pmatrix, row_count - 1, col_count - 1)), y);
}




TEST(monotype_matrix_test_suite, sets_all_cells) {
    double x = 8;
    size_t row_count = 2, col_count = 2;
    element_type* pdouble_type = new_double_element_type();

    matrix* pmatrix = new_monotype_matrix(pdouble_type);
    init_monotype_matrix(pmatrix, row_count, col_count);
    set_monotype_matrix(pmatrix, &x);

    int failures_count = 0;
    for(size_t row = 0; row < pmatrix->row_count; row++) {
        for(size_t col = 0; col < pmatrix->col_count; col++) {
            EXPECT_EQ(*((double*) get_cell_address(pmatrix, row, col)),
                        x 
            );
        }
    }
}


TEST(monotype_matrix_test_suite, adds_two_matrices) {
    double a = 1.0, b = 2;

    matrix* pA = new_monotype_matrix(new_double_element_type());
    matrix* pB = new_monotype_matrix(new_double_element_type());
    init_monotype_matrix(pA, 2, 2);
    init_monotype_matrix(pB, 2, 2);
    set_monotype_matrix(pA, &a);
    set_monotype_matrix(pB, &b);

    matrix* pC = add_monotype_matrices(pA, pB);

    for(size_t row = 0; row < pA->row_count; row++) {
        for(size_t col = 0; col < pA->col_count; col++) {
            EXPECT_EQ(
                *((double*) get_cell_address(pC, row, col)),
                *((double*) get_cell_address(pA, row, col)) + *((double*) get_cell_address(pB, row, col))
            );
        }
    }

}

TEST(monotype_matrix_test_suite, multiplies_two_matrices) {
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

