#ifndef MATRIX_H
    
    #define MATRIX_H

    #include <stdlib.h>
    #include <stddef.h>
    #include <assert.h>
    #include <stdio.h>
    #include "type_distribution.h"
    #include "storage.h"

    typedef struct matrix matrix;

    struct matrix {
        void* data;
        size_t row_count;
        size_t col_count;
        
        type_distribution* pdistr;
        storage* pstorage;
    };


    void* get_cell_address(matrix* pmat, size_t row, size_t col);
    void allocate_storage(matrix* pmatrix, size_t row, size_t col);
    element_type* get_cell_type(matrix* pmatrix, size_t row, size_t col);
    void set_cell(matrix* pmat, size_t row, size_t col, void* pvalue);
    void set_all_cells(matrix* pmatrix, void* pvalue);
    element* get_element(matrix* pmatrix, size_t row, size_t col);

    matrix* add_matrices(matrix* pA, matrix* pB);
    matrix* multiply_matrices(matrix* pA, matrix* pB);
    
    matrix* new_row_major_double_matrix();
    matrix* new_csv_generated_matrix(FILE* fp, storage* pstorage);
#endif
