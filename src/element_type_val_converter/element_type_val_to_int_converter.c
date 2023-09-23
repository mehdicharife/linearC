#include "../../include/element_type_val_to_int_converter.h"
#include "../../include/element_type.h"

int get_element_type_val_as_int(void* pval, element_type* ptype, element_type_val_to_int_converter* pconverter) {
    pconverter->input = pval;
    ptype->accept(ptype, (element_type_visitor*) pconverter);
    return pconverter->conversion;
}