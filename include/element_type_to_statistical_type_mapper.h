#ifndef ELEMENT_TYPE_TO_STATISTICAL_DATA_TYPE_MAPPER_H
#define ELEMENT_TYPE_TO_STATISTICAL_DATA_TYPE_MAPPER_H

#include "element_type_visitor.h"
#include "statistical_data_type.h"

typedef struct element_type_to_statistical_type_mapper element_type_to_statistical_type_mapper;

struct element_type_to_statistical_type_mapper {
    element_type_visitor parent;
    statistical_data_type type;
};

statistical_data_type get_statistical_data_type(element_type* ptype, element_type_to_statistical_type_mapper* pmapper);


#endif