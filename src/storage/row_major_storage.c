#include "../../include/row_major_storage.h"
#include <stdlib.h>


storage* new_row_major_storage() {
    storage* pstorage = (storage*) malloc(sizeof(storage));
    pstorage->get_cell_address = row_major_storage_get_cell_address;
    pstorage->allocate_storage = row_major_storage_allocate;

    return pstorage;
}

void* row_major_storage_get_cell_address(void* data, type_distribution* pdistr, size_t row_count, size_t col_count, size_t row, size_t col) {
    return ((char*) data) + pdistr->total_size_before(pdistr, row_count, col_count, lexicographical(), row, col);
}

void row_major_storage_allocate(void** pdata, type_distribution* pdistr, size_t row_count, size_t col_count) {
    size_t total_size = pdistr->total_size_before(pdistr, row_count, col_count, lexicographical(), row_count, 0);
    //printf("\n\n\nOut The Bowl\n\n\n");
    *pdata = malloc(total_size);
}
