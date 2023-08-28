#include "row_major_storage.h"

storage* new_row_major_storage() {
    storage* pstorage = (storage*) malloc(sizeof(storage));
    pstorage->get_cell_address = row_major_storage_get_cell_address;
    pstorage->allocate_storage = row_major_storage_allocate;

    return pstorage;
}

void* row_major_storage_get_cell_address(void* data, type_distribution* pdistr, size_t row_count, size_t col_count, size_t row, size_t col) {
    return pdistr->get_cell_type(pdistr, row_count, col_count, 0, 0)->pointer_addition(
        data,
        pdistr->total_size_before(pdistr, row_count, col_count, lexicographical, row, col)
    );
}

void row_major_storage_allocate(void** pdata, type_distribution* pdistr, size_t row_count, size_t col_count) {
    size_t total_size = pdistr->total_size_before(pdistr, row_count, col_count, lexicographical, row_count, 0);
    *pdata = malloc(total_size*(pdistr->get_cell_type(pdistr, row_count, col_count, 0, 0)->size));
}
