#include "nominal_data_type.h"

typedef struct string_based_nominal_data_type string_based_nominal_data_type;

struct string_based_nominal_data_type {
    nominal_data_type parent;
    char* val;
};

nominal_data_type* new_string_based_nominal_data_type(char* str);
char* string_based_nominal_data_type_get_val(nominal_data_type* pthis);