#ifndef NOMINAL_DATA_TYPE_H
#define NOMINAL_DATA_TYPE_H

typedef struct nominal_data_type nominal_data_type;

struct nominal_data_type {
    char* (*get_val)();
};


#endif

