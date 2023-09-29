#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include "../include/cgrid_design_matrix.h"

size_t get_statistical_data_type_count(cgrid_design_matrix* pmatrix, statistical_data_type type);

static statistical_data_type get_col_statistical_data_type_stub(cgrid_design_matrix* pmatrix, size_t j) {
    return (statistical_data_type) mock(pmatrix, j);
}

cgrid_design_matrix* pmatrix;

static void my_setup() {
    pmatrix = malloc(sizeof(cgrid_design_matrix));
    pmatrix->pgrid = malloc(sizeof(matrix));
    pmatrix->pgrid->col_count = 100;
    pmatrix->get_col_statistical_data_type = get_col_statistical_data_type_stub;
}


Describe(CGridDesignMatrixStatisticalFeatureCountGetter);
BeforeEach(CGridDesignMatrixStatisticalFeatureCountGetter) { my_setup(); }
AfterEach(CGridDesignMatrixStatisticalFeatureCountGetter) {}

Ensure(CGridDesignMatrixStatisticalFeatureCountGetter, returns_0_when_no_corresponding_feature_type_exists) {
    expect(get_col_statistical_data_type_stub, will_return(nominal));
    always_expect(get_col_statistical_data_type_stub, will_return(continuous));
    assert_that(get_statistical_data_type_count(pmatrix, ordinal), is_equal_to(0));
}

Ensure(CGridDesignMatrixStatisticalFeatureCountGetter, returns_1_when_featutre_type_exists_one_time_at_the_first_column) {
    expect(get_col_statistical_data_type_stub, will_return(count));
    always_expect(get_col_statistical_data_type_stub, will_return(continuous));
    assert_that(get_statistical_data_type_count(pmatrix, count), is_equal_to(1));
}

Ensure(CGridDesignMatrixStatisticalFeatureCountGetter, handles_ordinary_case) {
    expect(get_col_statistical_data_type_stub, will_return(ordinal));
    expect(get_col_statistical_data_type_stub, will_return(count));
    expect(get_col_statistical_data_type_stub, will_return(nominal));
    expect(get_col_statistical_data_type_stub, will_return(ordinal));
    expect(get_col_statistical_data_type_stub, will_return(nominal));
    always_expect(get_col_statistical_data_type_stub, will_return(continuous));

    assert_that(get_statistical_data_type_count(pmatrix, nominal),is_equal_to(2));
    
}


TestSuite* cgrid_design_matrix_statistical_feature_count_getter_test_suite() {
    TestSuite* suite = create_test_suite();
    add_test_with_context(suite, CGridDesignMatrixStatisticalFeatureCountGetter, returns_0_when_no_corresponding_feature_type_exists);
    add_test_with_context(suite, CGridDesignMatrixStatisticalFeatureCountGetter, returns_1_when_featutre_type_exists_one_time_at_the_first_column);
    add_test_with_context(suite, CGridDesignMatrixStatisticalFeatureCountGetter, handles_ordinary_case);
    return suite;
}