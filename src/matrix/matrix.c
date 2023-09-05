#include "../../include/matrix.h"
#include "../../include/uniform_type_distribution.h"
#include "../../include/row_major_storage.h"
#include "../../include/double_element_type.h"
#include "../../include/type_per_track_distribution.h"

void* get_cell_address(matrix* pmatrix, size_t row, size_t col) {
    return pmatrix->pstorage->get_cell_address(
        pmatrix->data,
        pmatrix->pdistr,
        pmatrix->row_count,
        pmatrix->col_count,
        row,
        col
    );
}

element_type* get_cell_type(matrix* pmatrix, size_t row, size_t col) {
    return pmatrix->pdistr->get_cell_type(pmatrix->pdistr, row, col);
}

void allocate_storage(matrix* pmatrix, size_t row_count, size_t col_count) {
    pmatrix->pstorage->allocate_storage(&(pmatrix->data), pmatrix->pdistr, row_count, col_count);
    pmatrix->row_count = row_count;
    pmatrix->col_count = col_count;
}


void set_cell(matrix* pmat, size_t row, size_t col, void* pvalue) {
    get_cell_type(pmat, row, col)->set(get_cell_address(pmat, row, col), pvalue);
}


void set_all_cells(matrix* pmatrix, void* pvalue) {
    assert(pmatrix->pdistr->get_type_count(pmatrix->pdistr) == 1);

    for(size_t row = 0; row < pmatrix->row_count; row++) {
        for(size_t col = 0; col < pmatrix->col_count; col++) {
            set_cell(pmatrix, row, col, pvalue);
        }
    }
}



element* get_element(matrix* pmatrix, size_t row, size_t col) {
    element* pelement = (element*) malloc(sizeof(element));

    pelement->ptype = get_cell_type(pmatrix, row, col);
    pelement->address = get_cell_address(pmatrix, row, col);

    return pelement;
}



matrix* add_matrices(matrix* pA, matrix* pB) {
    assert(pA->pdistr->equals(pA->pdistr, pB->pdistr) &&
           pA->pdistr->all_types_are_addable &&
           pA->row_count == pB->row_count &&
           pA->col_count == pB->col_count
    );

    matrix* pC = (matrix*) malloc(sizeof(matrix));
    pC->pdistr = pA->pdistr;
    pC->pstorage = pA->pstorage;
    allocate_storage(pC, pA->row_count, pA->col_count);

    for(size_t row = 0; row < pA->row_count; row++) {
        for(size_t col = 0; col < pA->col_count; col++) {    
            get_cell_type(pC, row, col)->add(
                get_cell_address(pA, row, col),
                get_cell_address(pB, row, col),
                get_cell_address(pC, row, col)
            );
        }
    }

    return pC;
}


matrix* multiply_matrices(matrix* pA, matrix* pB) {
    assert(pA->col_count == pB->row_count &&
           pA->pdistr->get_type_count(pA->pdistr) == 1 && 
           pB->pdistr->get_type_count(pB->pdistr) == 1 &&
           get_cell_type(pA, 0, 0) == get_cell_type(pB, 0, 0) &&
           get_cell_type(pA, 0, 0)->multiply != NULL &&
           get_cell_type(pB, 0, 0)->add != NULL
    );

    matrix* pC = (matrix*) malloc(sizeof(matrix));
    pC->pdistr = pA->pdistr;
    pC->pstorage = pA->pstorage;
    allocate_storage(pC, pA->row_count, pB->col_count);

    element_type* ptype = get_cell_type(pC, 0, 0);
    for(size_t row = 0; row < pC->row_count; row++) {
        for(size_t col = 0; col < pC->col_count; col++) {
            void* pvalue = ptype->get_addition_identity();
            for(size_t k = 0; k < pA->col_count; k++) {
                void* temp = ptype->multiply(
                    get_cell_address(pA, row, k),
                    get_cell_address(pB, k, col)
                );

                ptype->add(pvalue, temp, pvalue);

                free(temp);
            }

            set_cell(pC, row, col, pvalue);
            free(pvalue);
        }
    }

    return pC;
}



matrix* new_row_major_double_matrix() {
    matrix* pmatrix = malloc(sizeof(matrix));

    pmatrix->pdistr = new_uniform_type_distribution(new_double_element_type());
    pmatrix->pstorage = new_row_major_storage();

    return pmatrix;
}

matrix* new_csv_generated_matrix(FILE* fp, storage* pstorage) {
    //matrix* pmatrix = malloc(sizeof(matrix));
    //pmatrix->pstorage = pstorage;
    //type_distribution* pdsitr = new_type_distribution_from_csv_file(fp);

    return NULL;
}


