#include "element_type.h"


element_type* new_string_element_type();

void* (string_element_type_pointer_addition)(void* ptr, size_t offset);

void string_element_type_add(void* d1, void* d2, void* output);
void* string_element_type_get_addition_identity();


void string_element_type_set(void* tobesetted, void* pvalue);
bool string_element_type_are_equal(void* str1, void* str2);
bool string_element_type_matches_string(char* str);
void* string_element_type_get_from_string(char* str);
void string_element_type_print(void* pelement);
