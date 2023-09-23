#include "../include/element_type_to_statistical_type_naive_mapper.h"
#include <stdlib.h>

element_type_to_statistical_type_mapper* new_element_type_to_statistical_type_naive_mapper() {
    element_type_to_statistical_type_mapper* pmapper = malloc(sizeof(element_type_to_statistical_type_mapper));

    pmapper->parent.visit_int = element_type_to_statistical_type_naive_mapper_visit_int;
    pmapper->parent.visit_double = element_type_to_statistical_type_naive_mapper_visit_double;
    pmapper->parent.visit_string = element_type_to_statistical_type_naive_mapper_visit_string;

    return pmapper;
}

void element_type_to_statistical_type_naive_mapper_visit_int(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_to_statistical_type_mapper* pmapper = (element_type_to_statistical_type_mapper*) pvisitor;
    pmapper->type = count;
}

void element_type_to_statistical_type_naive_mapper_visit_double(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_to_statistical_type_mapper* pmapper = (element_type_to_statistical_type_mapper*) pvisitor;
    pmapper->type = continuous;
}

void element_type_to_statistical_type_naive_mapper_visit_string(element_type_visitor* pvisitor, element_type* ptype) {
    element_type_to_statistical_type_mapper* pmapper = (element_type_to_statistical_type_mapper*) pvisitor;
    pmapper->type = nominal;
}


