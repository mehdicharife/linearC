#include "../include/count_data_type.h"

int count_data_type_cmp(count_data_type* ptr1, count_data_type* ptr2) {
    return ptr1->get_val(ptr1) - ptr2->get_val(ptr2);
}