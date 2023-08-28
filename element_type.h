#ifndef ELEMENT_TYPE_H
    #define ELEMENT_TYPE_H

    #include <stddef.h>
    #include <stdbool.h>

    typedef struct element_type element_type;
    typedef struct element element;


    struct element_type {
        size_t size;
        void* (*pointer_addition) (void* a, size_t size);
        void (*add)(void* elem1, void* elem2, void* output);
        void (*subtract)(void* elem1, void* elem2, void* output);
        bool (*are_equal)(void* elem1, void* elem2);
        void* (*get_addition_identity)();
        void (*mult) (void* elem1, void* elem2, void* output);
        void* (*multiply)(void* elem1, void* elem2);
        void (*set)(void* ptobesetted, void* pvalue);
    }; 



    struct element {
        element_type* ptype;
        void* address;
    };

#endif