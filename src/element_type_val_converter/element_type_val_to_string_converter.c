#include "../../include/element_type_val_to_string_converter.h"
#include "../../include/element_type.h"

char* get_element_type_val_as_string(void* pval, element_type* ptype, element_type_val_to_string_converter* pconverter) {
    pconverter->input = pval;

    ptype->accept(ptype, (element_type_visitor*) pconverter);
    return pconverter->conversion;
}