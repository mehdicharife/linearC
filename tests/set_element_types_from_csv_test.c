
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <stdio.h>
#include "../include/element_type.h"
#include "../include/double_element_type.h"
#include "../include/int_element_type.h"



Test(set_element_types_from_csv_test_suite, handles_csv_file_with_one_type) {
    FILE* fp = tmpfile();
    fputs(".2, .6\n", fp);
    fputs("5.2, .3", fp);
    rewind(fp);

    element_type** types = NULL;
    size_t type_count;
    set_element_types_from_csv_file(&types, &type_count, fp);
    
    cr_assert(eq(int, type_count, 2));

    for(size_t k = 0; k < type_count; k++) {
        cr_expect(eq(ptr, types[k], new_double_element_type()));
    }
}

Test(set_element_types_from_csv_test_suite, handles_csv_file_with_type_per_col) {
    FILE* fp = tmpfile();
    fputs("1.2, 5\n", fp);
    fputs(".5, 1\n", fp);
    rewind(fp);

    element_type** types = NULL;
    size_t type_count;
    set_element_types_from_csv_file(&types, &type_count, fp);
    
    cr_assert(not(eq(ptr, types, NULL)));
    cr_assert(eq(int, type_count, 2));
    for(size_t k = 0; k < type_count; k++) {
        cr_expect(eq(ptr, types[k], (k == 0)? new_double_element_type() : new_int_element_type()));
    }

    fclose(fp);
}

Test(set_element_types_from_csv_test_suite, handles_csv_with_multiple_types_per_col) {
    FILE* fp = tmpfile();
    fputs("1.2, 5\n", fp);
    fputs("2, 3\n", fp);
    rewind(fp);

    element_type** types = NULL;
    size_t type_count;
    set_element_types_from_csv_file(&types, &type_count, fp);

    cr_assert(not(eq(ptr, types, NULL)));
    cr_assert(eq(int, type_count, 2));
    for(size_t k = 0; k < type_count; k++) {
        cr_expect(eq(ptr, types[k], (k == 0) ? new_double_element_type() : new_int_element_type()));
    }
}





