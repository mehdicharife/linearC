#include "monotype_matrix.h"
#include <string.h>

matrix* new_monotype_matrix(element_type* ptype) {
    monotype_matrix* pmatrix = (monotype_matrix*) malloc(sizeof(monotype_matrix));
 
    pmatrix->ptype = ptype;

    pmatrix->parent.get_offset = monotype_matrix_get_offset;
    pmatrix->parent.get_cell_type = monotype_matrix_get_cell_type;
    
    pmatrix->parent.row_count = 0;
    pmatrix->parent.col_count = 0;

    return (matrix*) pmatrix;
}


void init_monotype_matrix(matrix* pmatrix, size_t row_count, size_t col_count) {
    element_type* ptype = (element_type*) ((monotype_matrix*) pmatrix)->ptype;

    pmatrix->data = malloc(row_count*col_count*(ptype->size));
    pmatrix->row_count = row_count;
    pmatrix->col_count = col_count;
}

void set_monotype_matrix(matrix* pmatrix, void* pvalue) {
    size_t row_count = pmatrix->row_count;
    size_t col_count = pmatrix->col_count;

    for(size_t i = 0; i < row_count; i++) {
        for(size_t j = 0; j < col_count; j++) {
            set_cell(pmatrix, i, j, pvalue);
        }
    }

}


size_t monotype_matrix_get_offset(matrix* pmatrix, size_t row, size_t col) {
    size_t element_size = ((monotype_matrix*) pmatrix)->ptype->size;
    size_t col_count = pmatrix->col_count;
    size_t row_count = pmatrix->row_count;

    return (row*col_count + col);
}

element_type* monotype_matrix_get_cell_type(matrix* pmatrix, size_t row, size_t col) {
    return ((monotype_matrix*) pmatrix)->ptype;
}


matrix* add_monotype_matrices(matrix* pA, matrix* pB) {
    assert(pA->col_count == pB->col_count && pA->row_count == pB->row_count);

    monotype_matrix* pmA = (monotype_matrix*) pA;
    monotype_matrix* pmB = (monotype_matrix*) pB;
    assert(pmA->ptype == pmB->ptype);

    element_type* ptype = pmA->ptype;

    matrix* pmC =  new_monotype_matrix(pmA->ptype);
    init_monotype_matrix(pmC, pA->row_count, pA->col_count);
    for(size_t row = 0; row < pA->row_count; row++) {
        for(size_t col = 0; col < pA->col_count; col++) {
            ptype->add(
                get_cell_address(pA, row, col),
                get_cell_address(pB, row, col),
                get_cell_address(pmC, row, col)
            );
        }
    }

    return pmC;
}


matrix* multiply_monotype_matrices(matrix* pA, matrix* pB) {
    assert(pA->col_count == pB->row_count &&
           (((monotype_matrix*) pA)->ptype == ((monotype_matrix*) pB)->ptype)
    );

    element_type* ptype = ((monotype_matrix*) pA)->ptype;
    matrix* pC = new_monotype_matrix(ptype);
    init_monotype_matrix(pC, pA->row_count, pB->col_count);

    for(size_t row = 0; row < pC->row_count; row++) {
        for(size_t col = 0; col < pC->col_count; col++) {
            set_cell(pC, row, col, ptype->get_addition_identity());

            for(size_t k = 0; k < pA->col_count; k++) {
                void* temp = ptype->multiply(
                    get_cell_address(pA, row, k),
                    get_cell_address(pB, col, k)
                );

                ptype->add(
                    get_cell_address(pC, row, col),
                    temp,
                    get_cell_address(pC, row, col)
                );


                free(temp);
            }
        }
    }

    
    return pC;
}