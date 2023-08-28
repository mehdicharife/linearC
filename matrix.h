#ifndef MATRIX_H
    
    #define MATRIX_H

    #include <stdlib.h>
    #include <stddef.h>
    #include <assert.h>
    #include "type_distribution/type_distribution.h"
    #include "storage/storage.h"

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
    void set_cell(matrix* pmat, size_t row, size_t col, void* pvalue);
    element* get_element(matrix* pmatrix, size_t row, size_t col);

    matrix* add_matrices(matrix* pA, matrix* pB);

#endif
