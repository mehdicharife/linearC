#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include <stdio.h>
#include "../include/matrix.h"
#include "../include/row_major_storage.h"
#include "../include/get_untill.h"
#include "../include/element_type_eloquence_cmp.h"



storage* pstorage;


void setup(void) {
    pstorage = new_row_major_storage();
}

TestSuite(new_csv_generated_matrix_test_suite, .init=setup);



#define FILES_COUNT 1
#define FILES_PATHS (char*[]) {"/home/mehdi/linearC/tests/subjects/uniform_str.csv"}
ParameterizedTestParameters(new_csv_generated_matrix_test_suite, creates_matrix_from_csv_file) {
    static char* files_paths[FILES_COUNT];
    for(size_t k = 0; k < FILES_COUNT; k++) {
        files_paths[k] = cr_malloc(strlen(FILES_PATHS[k]) + 1);
        strcpy(files_paths[k], FILES_PATHS[k]);
    }

    return cr_make_param_array(char*, files_paths, FILES_COUNT);
}



ParameterizedTest(char** p_test_file_path, new_csv_generated_matrix_test_suite, creates_matrix_from_csv_file) {
    FILE* fp = fopen(*p_test_file_path, "r");
    
    if(fp == NULL) {
        perror("couldn't open file?");
    }

    matrix* pmatrix = new_csv_generated_matrix(fp, pstorage);

    rewind(fp);
    char* curr_cell_as_str;
    char stop_cause;
    for(size_t row = 0; row < pmatrix->row_count; row++) {
        for(size_t col = 0; col < pmatrix->col_count; col++) {
            curr_cell_as_str = csv_get_untill_delim(fp, &stop_cause);
            element_type* curr_type = get_cell_type(pmatrix, row, col);

            element_type** types;
            size_t type_count;
            set_to_supported_element_types(&types, &type_count);
            element_type* str_type  = get_element_type_from_str(curr_cell_as_str, types, type_count);
            cr_assert(ge(int, element_type_eloquence_cmp(curr_type, str_type), 0));
            
            void* expected = curr_type->get_from_string(curr_cell_as_str);
            void* got = get_cell_address(pmatrix, row, col);
            cr_expect(curr_type->are_equal(got, expected));
            
            free(expected);
        }
    }

}