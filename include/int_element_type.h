#include "element_type.h"


element_type* new_int_element_type();

void* (int_element_type_pointer_addition)(void* ptr, size_t offset);

void int_element_type_add(void* d1, void* d2, void* output);
void int_element_type_substract(void* pd1, void* pd2, void* output);
void* int_element_type_get_addition_identity();

void* int_element_type_multiply(void* px, void* py);

void int_element_type_set(void* tobesetted, void* pvalue);
bool int_element_type_are_equal(void* px, void* py);
bool int_element_type_matches_string(char* str);
void* int_element_type_get_from_string(char* str);
void int_element_type_print(void* pelement);
