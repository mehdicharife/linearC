#ifndef STATISTICAL_DATA_TYPE_H
#define STATISTICAL_DATA_TYPE_H

#include "element_type.h"
#include <stdbool.h>


enum statistical_data_type {
    continuous,
    count,
    binomial,
    ordinal,
    nominal,
    binary,
    undefined,
};

typedef enum statistical_data_type statistical_data_type;


typedef struct continuous_data_type continuous_data_type;
typedef struct ordinal_data_type ordinal_data_type;
typedef struct nominal_data_type nominal_data_type;
typedef struct count_data_type count_data_type;





#endif