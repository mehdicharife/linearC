#include <assert.h>
#include <stdlib.h>
#include "../../include/element_type.h"
#include "../../include/double_element_type.h"
#include "../../include/int_element_type.h"
#include "../../include/string_element_type.h"
#include "../../include/get_untill.h"
#include "../../include/element_type_eloquence_cmp.h"
#include <unistd.h>

void set_to_supported_element_types(element_type*** parr, size_t* parray_size) {
    *parray_size = 3;
    *parr = malloc(*parray_size*sizeof(element_type*));
    (*parr)[0] = new_double_element_type();
    (*parr)[1] = new_int_element_type();
    (*parr)[2] = new_string_element_type();
}

element_type* get_element_type_from_str(char* str, element_type** types, size_t type_count) {
    for(size_t k = 0; k < type_count; k++) {
        if(types[k]->matches_string(str)) {
            return types[k];
        }
    }

    return NULL;
}


void set_element_types_from_csv_file(element_type*** types, size_t* ptype_count, FILE* fp) {
    assert(fp != NULL);

    size_t supported_types_count;
    element_type** supported_types ;
    set_to_supported_element_types(&supported_types, &supported_types_count);

    char delimiters[] = {',', '\n'};
    size_t delimiters_count = 2;

    size_t type_count = 12;
    *types = malloc(type_count*sizeof(element_type*));
    size_t curr_type_index = 0;
    set_to_least_eloquent(*types, type_count);

    char* curr_str;
    char stop_cause;
    while((curr_str = get_untill_delim(fp, delimiters, delimiters_count, &stop_cause)) != NULL) {


        (*types)[curr_type_index] = get_most_eloquent_type(
            (*types)[curr_type_index],
            get_element_type_from_str(curr_str, supported_types, supported_types_count)
        );

        if(stop_cause != '\n') {
            curr_type_index++; 
        } else {
            *ptype_count = curr_type_index + 1;
            curr_type_index = 0;
        }
        
    }

}





