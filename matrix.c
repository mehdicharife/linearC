#include "matrix.h"

void* get_cell_address(matrix* pmatrix, size_t row, size_t col) {
    return pmatrix->get_cell_type(pmatrix, 0, 0)->pointer_addition(
        pmatrix->data,
        pmatrix->get_offset(pmatrix, row, col)
    );
}

element* get_element(matrix* pmatrix, size_t row, size_t col) {
    element* pelement = (element*) malloc(sizeof(element));

    pelement->ptype = pmatrix->get_cell_type(pmatrix, row, col);
    pelement->address = get_cell_address(pmatrix, row, col);

    return pelement;
}


void set_cell(matrix* pmat, size_t row, size_t col, void* pvalue) {
    pmat->get_cell_type(pmat, row, col)->set(get_cell_address(pmat, row, col), pvalue);
}