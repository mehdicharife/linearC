#ifndef MATRIX_H
    
    #define MATRIX_H

    #include <stdlib.h>
    #include <stddef.h>
    #include <assert.h>
    #include "element_type.h"

    typedef struct matrix matrix;


    struct matrix {
        void* data;
        size_t row_count;
        size_t col_count;
        
        size_t (*get_offset)(matrix* pthis, size_t row, size_t col);
        void* (*get_cell_address)(matrix* pthis, size_t row, size_t col);
        element_type* (*get_cell_type)(matrix* pthis, size_t row, size_t col);
        void* (*allocate_storage)(matrix* pthis);
    };


    void* get_cell_address(matrix* pmat, size_t row, size_t col);
    element* get_element(matrix* pmatrix, size_t row, size_t col);
    void set_cell(matrix* pmat, size_t row, size_t col, void* pvalue);
    size_t get_type_count(matrix* pmatrix);

#endif





/*
matrix* add(matrix* pA, matrix* pB) {
    assert(pA->ptype == pB->ptype &&
           pA->row_count == pB->row_count &&
           pA->col_count == pB->col_count
    );


    matrix* pC = malloc(sizeof(matrix));
    pC->ptype = ptype;
    init_matrix(pC, pA->ptype, pA->row_count, pB->col_count);
    
    for(size_t i = 0; i < pC->row_count; i++) {
        for(size_t j = 0; j < pC->col_count; j++) {
            void* A_element_address = get_element_address(pA, i, j));
            void* B_element_address = get_element_address(pB, i, j));
            void* C_element_address = get_element_address(pC, i, j));

            pC->ptype->add(A_element_address, B_element_address, C_element_address);
        }
    }


    return pC;
};
*/

