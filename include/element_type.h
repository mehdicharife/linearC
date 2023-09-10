#ifndef ELEMENT_TYPE_H
    #define ELEMENT_TYPE_H

    #include <stddef.h>
    #include <stdbool.h>
    #include <stdio.h>

    typedef struct element_type element_type;
    typedef struct element element;

    element_type* new_no_type();

    struct element_type {
        size_t size;
        char* name;
        void* (*pointer_addition) (void* a, size_t size);
        void (*add)(void* elem1, void* elem2, void* output);
        void (*subtract)(void* elem1, void* elem2, void* output);
        bool (*are_equal)(void* elem1, void* elem2);
        void* (*get_addition_identity)();
        void (*mult) (void* elem1, void* elem2, void* output);
        void* (*multiply)(void* elem1, void* elem2);
        void (*set)(void* ptobesetted, void* pvalue);
        bool (*matches_string)(char* str);
        void* (*get_from_string)(char* str); 
        void (*print)(void* pelement);       
    }; 



    struct element {
        element_type* ptype;
        void* address;
    };

    void set_to_supported_element_types(element_type*** parr, size_t* parray_size);
    
    element_type* get_element_type_from_str(char* str, element_type** types, size_t type_count);
    void set_element_types_from_csv_file(element_type*** types, size_t* ptype_count, FILE* fp);

#endif