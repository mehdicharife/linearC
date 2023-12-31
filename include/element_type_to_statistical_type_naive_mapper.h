#include "element_type_to_statistical_type_mapper.h"

element_type_to_statistical_type_mapper* new_element_type_to_statistical_type_naive_mapper();

void element_type_to_statistical_type_naive_mapper_visit_int(element_type_visitor* pvisitor, element_type* ptype);
void element_type_to_statistical_type_naive_mapper_visit_double(element_type_visitor* pvisitor, element_type* ptype);
void element_type_to_statistical_type_naive_mapper_visit_string(element_type_visitor* pvisitor, element_type* ptype);