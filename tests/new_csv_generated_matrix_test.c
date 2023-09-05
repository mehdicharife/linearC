#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/matrix.h"
#include "../include/row_major_storage.h"
#include "../include/get_untill.h"
#include <stdio.h>


storage* pstorage;

void setup(void) {
    pstorage = new_row_major_storage();
}

TestSuite(new_csv_generated_matrix_test_suite, .init=setup);

Test(new_csv_generated_matrix_test_suite, basic) {
    FILE* fp = fopen("subjects/basic.csv", "r");
    matrix* pmatrix = new_csv_generated_matrix(fp, pstorage);

    char* curr_cell_as_str;
    char* stop_cause;
    for(size_t row = 0; row < pmatrix->row_count; row++) {
        for(size_t col = 0; col < pmatrix->col_count; col++) {
            curr_cell_as_str = csv_get_untill_delim(fp, stop_cause);
            element_type* curr_type = get_cell_type(pmatrix, row, col);
            cr_assert(curr_type->matches_string(curr_cell_as_str));
            
            void* expected = curr_type->get_from_string(curr_cell_as_str);
            void* got = get_cell_address(pmatrix, row, col);
            cr_expect(curr_type->are_equal(got, expected));
            
            free(expected);
        }
    }

}