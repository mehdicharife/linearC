#include "../include/nominal_data_type.h"
#include <string.h>
#include <stdio.h>

int nominal_data_type_cmp(nominal_data_type* ptr1, nominal_data_type* ptr2) {
    return strcmp(ptr1->get_val(ptr1), ptr2->get_val(ptr2));
}