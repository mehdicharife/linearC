#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/matrix.h"


Test(row_major_double_matrix_test_suite, sets_a_cell) {
    double x = 5.0;
    double y = 8.0;

    size_t row_count = 3, col_count = 2;

    matrix* pmatrix = new_row_major_double_matrix();
    allocate_storage(pmatrix, row_count, col_count);


    set_cell(pmatrix, 0, 0, &x);
    element_type* ptype1 = get_cell_type(pmatrix, 0, 0);
    cr_expect(ptype1->are_equal(get_cell_address(pmatrix, 0, 0), &x));

    set_cell(pmatrix, 1, 1, &y);
    element_type* ptype2 = get_cell_type(pmatrix, 1, 1);
    cr_expect(ptype2->are_equal(get_cell_address(pmatrix, 1, 1), &y));
}


Test(row_major_double_matrix_test_suite, sets_all_cells) {
    double x = 8;
    size_t row_count = 8, col_count = 2;

    matrix* pmatrix = new_row_major_double_matrix();
    allocate_storage(pmatrix, row_count, col_count);
    set_all_cells(pmatrix, &x);

    
    for(size_t row = 0; row < pmatrix->row_count; row++) {
        for(size_t col = 0; col < pmatrix->col_count; col++) {
            cr_expect(get_cell_type(pmatrix, row, col)->are_equal(
                get_cell_address(pmatrix, row, col), &x
            ));
        }
    }
}


Test(row_major_double_matrix_test_suite, adds_two_matrices) {
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
            element_type* cell_type = get_cell_type(pC, row, col);
            void* pexpected = malloc(cell_type->size);
            cell_type->add(get_cell_address(pA, row, col), get_cell_address(pB, row, col), pexpected);

            cr_expect(cell_type->are_equal(
                    get_cell_address(pC, row, col),
                    pexpected
            ));

            free(pexpected);
        }
    }

}


Test(row_major_double_matrix_test_suite, multiplies_two_matrices) {
    matrix* pA = new_row_major_double_matrix();
    matrix* pB = new_row_major_double_matrix();
    allocate_storage(pA, 3, 3);
    allocate_storage(pB, 3, 5);

    double a = 2;
    double b = 3;
    set_all_cells(pA, &a);
    set_all_cells(pB, &b);

    matrix* pC = multiply_matrices(pA, pB);
    element_type* ptype = get_cell_type(pC, 0, 0);
    
    for(size_t row = 0; row < pC->row_count; row++) {
        for(size_t col = 0; col < pC->col_count; col++) {
            void* pexpected = ptype->get_addition_identity();
            for(size_t k = 0; k < pA->col_count; k++) {
                void* temp = ptype->multiply(
                    get_cell_address(pA, row, k),
                    get_cell_address(pB, k, col)
                );

                ptype->add(pexpected, temp, pexpected);
                
                free(temp);
            }


            cr_expect(ptype->are_equal(
                get_cell_address(pC, row, col),
                pexpected
            ));

            free(pexpected);
        }
    }

}