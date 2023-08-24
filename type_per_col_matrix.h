#include "matrix.h"


typedef struct type_per_col_matrix type_per_col_matrix;

struct type_per_col_matrix {
    matrix parent;
    element_type* types;
    size_t type_count;
};

void* type_per_col_martrix_get_cell_address(matrix* pmatrix, size_t row, size_t col) {
    void* data = pmatrix->data;
}
