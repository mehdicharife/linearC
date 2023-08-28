#ifndef ROW_MAJOR_STORAGE_H

    #define ROW_MAJOR_STORAGE_H

    #include "storage.h"

    storage* new_row_major_storage();
    void* row_major_storage_get_cell_address(void* data, type_distribution* pdistr, size_t row_count, size_t col_count, size_t row, size_t col);
    void row_major_storage_allocate(void** pdata, type_distribution* pdistr, size_t row_count, size_t col_count);

#endif
