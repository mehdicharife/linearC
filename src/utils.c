#include "../include/utils.h"
#include <string.h>

int get_str_index(char** array, size_t array_size, char* value) {
    for(size_t i = 0; i < array_size; i++) {
        if(!strcmp(array[i], value)) {
            return i;
        }
    }
    return -1;
}


int get_char_index(char* array, size_t array_size, char value) {
    for(size_t i = 0; i < array_size; i++) {
        if(array[i] == value) {
            return i;
        }
    }
    return -1;
}