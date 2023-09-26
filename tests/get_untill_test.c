#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/get_untill.h"
#include <stdio.h>
#include "../include/string_element_type.h"
#include <unistd.h>


char delimiters[2] = {',', '\n'};
int delimiters_count = 2;



Test(get_untill_delim_test_suite, gets_first_element) {
    char* expected = "Joe Blake";
    FILE* fp = tmpfile();
    fputs(expected, fp);
    fputs(", 28, Truck driver\n", fp);
    fputs("Juliana Crane, 29, Secretary\n", fp);
    rewind(fp);

    char* got = get_untill_delim(fp, delimiters, delimiters_count, NULL); 
    char* got2 = get_untill_delim(fp, delimiters, delimiters_count, NULL);       
    
    cr_assert(eq(str, got, expected));
    cr_assert(eq(str, got2, "28"));
}


Test(get_untill_delim_test_suite, returns_empty_string_when_nothing_before_delimiter) {
    FILE* fp = tmpfile();
    fputs(",", fp);
    rewind(fp);

    char* got = get_untill_delim(fp, delimiters, delimiters_count, NULL);

    cr_assert(eq(str, "", got));
}


Test(get_untill_delim_test_suite, ignores_surrounding_spaces) {
    char* expected = "John Smith";
    FILE* fp = tmpfile();
    fputs("  ", fp);
    fputs(expected, fp);
    fputs(" ,", fp);
    rewind(fp);

    char* got = get_untill_delim(fp, delimiters, delimiters_count, NULL);

    cr_assert(eq(str, got, expected));
}


Test(get_untill_delim_test_suite, stops_at_new_line) {
    char* expected = "Trudy Walker";
    FILE* fp = tmpfile();
    fputs(expected, fp);
    fputs("\n", fp);
    rewind(fp);

    char* got = get_untill_delim(fp, delimiters, delimiters_count, NULL);

    cr_assert(eq(str, got, expected));
}


Test(get_untill_delim_test_suite, handles_delimiter_inside_quotes) {
    char* expected = "\"Braund, Mr. Owen Harris\"";
    FILE* fp = tmpfile();
    fputs("1,0,3,", fp);
    fputs(expected, fp);
    fputs(",male,22,1,0,A/5 21171,7.25,,S", fp);
    rewind(fp);

    char* got;
    for(size_t k = 0; k < 4; k++) {
        got = get_untill_delim(fp, delimiters, delimiters_count, NULL);
        //new_string_element_type()->print(&got);
        //sleep(1);
    }
    

    cr_assert(eq(str, got, expected));
}



Test(get_untill_delim_test_suite, handles_multiple_quotes) {
    char* expected = "\"Foo\" \",bar\"";
    FILE* fp = tmpfile();
    fputs(expected, fp);
    rewind(fp);

    char* got = get_untill_delim(fp, delimiters, delimiters_count, NULL);

    cr_assert(eq(str, got, expected));
}

Test(get_untill_delim_test_suite, returns_NULL_at_EOF) {
    FILE* fp = tmpfile();
    cr_expect(eq(ptr, get_untill_delim(fp, delimiters, delimiters_count, NULL), NULL));
}


/*
Test(get_untill_delim_test_suite, can_be_used_to_make_exact_copy_of_file) {
    FILE* fp = fopen("tests/subjects/titanic.csv", "r");
    if(fp == NULL) {
        perror("fopen() failed");
    }

    FILE* copy = fopen("tests/subjects/titanic_copy.csv", "w");
    if(copy == NULL) {
        perror("fopen failed");
    }


    char* curr_str;
    char stop_cause_delimiter;
    while(!feof(fp)) {
        curr_str = get_untill_delim(fp, delimiters, delimiters_count, &stop_cause_delimiter);
        fputs(curr_str, copy);
        free(curr_str);
        if(stop_cause_delimiter != EOF) { fputc(stop_cause_delimiter, copy); }
    }

    fclose(fp);
    fclose(copy);
} 
*/


Test(get_untill_delim_test_suite, sets_dimensions) {
    FILE* fp = tmpfile();
    fputs("1, 2,0\n3,4,8", fp);
    rewind(fp);

    size_t got_row, got_col, expected_row, expected_col;
    expected_row = 2;
    expected_col = 3;
    set_dimensions(fp, &got_row, &got_col);

    cr_expect(eq(int, (int) got_row, (int) expected_row));
    cr_expect(eq(int, (int) got_col, (int) expected_col));
}