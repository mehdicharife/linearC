#include "element_type.h"

int element_type_eloquence_cmp(element_type* ptype1, element_type* ptype2);
element_type* get_most_eloquent_type(element_type* ptype1, element_type* ptype2);
element_type* new_least_eloquent();
void set_to_least_eloquent(element_type** arr, size_t arr_size);
