#include "../../include/element_type_val_to_double_converter.h"
#include "../../include/element_type.h"

double get_element_type_val_as_double(void* pval, element_type* ptype, element_type_val_to_double_converter* pconverter) {
    pconverter->input = pval;
    ptype->accept(ptype, (element_type_visitor*) pconverter);
    return pconverter->conversion;
}