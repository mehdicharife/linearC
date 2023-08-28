#include "matrix.h"

typedef struct monotype_matrix monotype_matrix;

struct monotype_matrix {
    matrix parent;
};

matrix* new_monotype_matrix(element_type* ptype);
size_t monotype_matrix_get_offset(matrix* pmatrix, size_t row, size_t col);
element_type* monotype_matrix_get_cell_type(matrix* pmatrix, size_t row, size_t col);

matrix* add_monotype_matrices(matrix* pA, matrix* pB);
matrix* multiply_monotype_matrices(matrix* pA, matrix* pB);