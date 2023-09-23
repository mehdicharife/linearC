#include "../include/element_type_to_statistical_type_mapper.h"


statistical_data_type get_statistical_data_type(element_type* ptype, element_type_to_statistical_type_mapper* pmapper) {
    ptype->accept(ptype, (element_type_visitor*) pmapper);
    return pmapper->type; 
}