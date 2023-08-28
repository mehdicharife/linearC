#ifndef STORAGE_H

    #define STORAGE_H


    #include "../type_distribution/type_distribution.h"

    typedef struct storage storage;

    struct storage {
        void* (*get_cell_address)(void* data, type_distribution* pdistr, size_t row_count, size_t col_count, size_t row, size_t col);
        void (*allocate_storage)(void** pdata, type_distribution* pdistr, size_t row_count, size_t col_count);
    };

#endif

