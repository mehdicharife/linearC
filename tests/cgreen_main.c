#include <cgreen/cgreen.h>

TestSuite* cgrid_design_matrix_column_statistical_type_getter_test_suite();
TestSuite* cgrid_design_matrix_jth_statistical_feature_col_index_getter_test_suite();
TestSuite* cgrid_design_matrix_statistical_feature_count_getter_test_suite();


int main(int argc, char **argv) {
    TestSuite *suite = create_test_suite();
    add_suite(suite, cgrid_design_matrix_column_statistical_type_getter_test_suite());
    add_suite(suite, cgrid_design_matrix_jth_statistical_feature_col_index_getter_test_suite());
    add_suite(suite, cgrid_design_matrix_statistical_feature_count_getter_test_suite());

    return run_test_suite(suite, create_text_reporter());
}
