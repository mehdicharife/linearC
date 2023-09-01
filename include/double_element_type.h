#include "element_type.h"


element_type* new_double_element_type();

void* (double_element_type_pointer_addition)(void* ptr, size_t offset);

void double_element_type_add(void* d1, void* d2, void* output);
void double_element_type_substract(void* pd1, void* pd2, void* output);
void* double_element_type_get_addition_identity();

void* double_element_type_multiply(void* px, void* py);

void double_element_type_set(void* tobesetted, void* pvalue);
bool double_element_type_are_equal(void* px, void* py);
bool double_element_type_matches_string(char* str);

