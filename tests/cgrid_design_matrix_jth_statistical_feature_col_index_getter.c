#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include "../include/cgrid_design_matrix.h"

int get_jth_statistical_feature_col_index(cgrid_design_matrix* pmatrix, statistical_data_type ptype, size_t j);


statistical_data_type get_col_statistical_data_type_stub(cgrid_design_matrix* pmatrix, size_t col) {
    return (statistical_data_type) mock(pmatrix, col);
}

static cgrid_design_matrix* pmatrix;

void my_setup() {
    pmatrix = malloc(sizeof(cgrid_design_matrix));
    pmatrix->pgrid = malloc(sizeof(matrix));
    pmatrix->pgrid->col_count = 100;
    pmatrix->get_col_statistical_data_type = get_col_statistical_data_type_stub;
}


Describe(CGridDesignMatrixJthStatisticalFeatureColIndexGetter);
BeforeEach(CGridDesignMatrixJthStatisticalFeatureColIndexGetter) { my_setup(); }
AfterEach(CGridDesignMatrixJthStatisticalFeatureColIndexGetter) {}



Ensure(CGridDesignMatrixJthStatisticalFeatureColIndexGetter, returns_zero_when_asked_about_col_index_of_zeroth_feature_that_is_at_the_first_column) {
    expect(get_col_statistical_data_type_stub, will_return(ordinal));
    never_expect(get_col_statistical_data_type_stub);
    assert_that(get_jth_statistical_feature_col_index(pmatrix, ordinal, 0), is_equal_to(0));
}

Ensure(CGridDesignMatrixJthStatisticalFeatureColIndexGetter, handles_non_existing_feature_type_by_returning_minus_one) {
    always_expect(get_col_statistical_data_type_stub, will_return(nominal));
    assert_that(get_jth_statistical_feature_col_index(pmatrix, count, 1), is_equal_to(-1));
}

Ensure(CGridDesignMatrixJthStatisticalFeatureColIndexGetter, handles_case_where_j_surpasses_feature_type_count) {
    expect(get_col_statistical_data_type_stub, will_return(ordinal));
    expect(get_col_statistical_data_type_stub, will_return(nominal));
    expect(get_col_statistical_data_type_stub, will_return(continuous));
    expect(get_col_statistical_data_type_stub, will_return(nominal));
    always_expect(get_col_statistical_data_type_stub, will_return(count));

    assert_that(get_jth_statistical_feature_col_index(pmatrix, nominal, 2), is_equal_to(-1));
}

Ensure(CGridDesignMatrixJthStatisticalFeatureColIndexGetter, handles_these_cases) {
    expect(get_col_statistical_data_type_stub, will_return(continuous));
    expect(get_col_statistical_data_type_stub, will_return(nominal));
    expect(get_col_statistical_data_type_stub, will_return(continuous));
    never_expect(get_col_statistical_data_type_stub);

    assert_that(get_jth_statistical_feature_col_index(pmatrix, continuous, 1), is_equal_to(2));
}

TestSuite* cgrid_design_matrix_jth_statistical_feature_col_index_getter_test_suite() {
    TestSuite* sweet = create_test_suite();
    add_test_with_context(sweet, CGridDesignMatrixJthStatisticalFeatureColIndexGetter, returns_zero_when_asked_about_col_index_of_zeroth_feature_that_is_at_the_first_column);
    add_test_with_context(sweet, CGridDesignMatrixJthStatisticalFeatureColIndexGetter, handles_non_existing_feature_type_by_returning_minus_one);
    add_test_with_context(sweet, CGridDesignMatrixJthStatisticalFeatureColIndexGetter, handles_case_where_j_surpasses_feature_type_count);
    add_test_with_context(sweet, CGridDesignMatrixJthStatisticalFeatureColIndexGetter, handles_these_cases);
    return sweet;
}
