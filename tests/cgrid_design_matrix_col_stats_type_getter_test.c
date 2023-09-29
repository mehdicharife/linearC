#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include "../include/cgrid_design_matrix.h"

//TestSuite* cgrid_design_matrix_jth_statistical_feature_col_index_getter_test_suite();


statistical_data_type get_col_statistical_data_type(cgrid_design_matrix* pmatrix, size_t col_index);

static element_type_to_statistical_type_mapper* stub_mapper;
static matrix* cgrid_stub;
static type_distribution* pdistr;
static cgrid_design_matrix* pmatrix;

element_type* get_cell_type_stub(type_distribution* pdistr, size_t row, size_t col) {
    return (element_type*) mock(pdistr, row, col);
}

void visit_double_stub(element_type_visitor* pvisitor, element_type* ptype) {
    mock(pvisitor, ptype);
}
void visit_int_stub(element_type_visitor* pvisitor, element_type* ptype) {
    mock(pvisitor, ptype);
}
void visit_string_stub(element_type_visitor* pvisitor, element_type* ptype) {
    mock(pvisitor, ptype);
}


static void my_setup() {
    cgrid_stub = malloc(sizeof(matrix));
    pdistr = malloc(sizeof(type_distribution));
    pdistr->get_cell_type = get_cell_type_stub;
    cgrid_stub->pdistr = pdistr;

    stub_mapper = malloc(sizeof(element_type_to_statistical_type_mapper));
    stub_mapper->parent.visit_double = visit_double_stub;
    stub_mapper->parent.visit_int = visit_int_stub;
    stub_mapper->parent.visit_string = visit_string_stub;

    pmatrix = (cgrid_design_matrix*) new_cgrid_design_matrix(cgrid_stub, stub_mapper);
    free(pmatrix->statistical_types);
    pmatrix->statistical_types = malloc(sizeof(statistical_data_type)*10);
    for(size_t k = 0; k < 10; k++) {
        pmatrix->statistical_types[k] = undefined;
    }
    
}


Describe(CGridDesignMatrixColStatsTypeGetter);
BeforeEach(CGridDesignMatrixColStatsTypeGetter) { my_setup(); }
AfterEach(CGridDesignMatrixColStatsTypeGetter) { }

Ensure(CGridDesignMatrixColStatsTypeGetter, returns_mapped_statistical_data_type_if_overriding_type_is_undefined) {
    expect(get_cell_type_stub, when(col, is_equal_to(1)), will_return(new_double_element_type()));
    
    expect(visit_double_stub, when(ptype, is_equal_to(new_double_element_type())));
    
    get_col_statistical_data_type(pmatrix, 1);
}

Ensure(CGridDesignMatrixColStatsTypeGetter, returns_immediately_if_overriding_statistical_data_type_is_not_undefined) {
    pmatrix->statistical_types[0] = continuous;
    never_expect(get_cell_type_stub);
    never_expect(visit_double_stub);
    get_col_statistical_data_type(pmatrix, 0);
}





TestSuite *cgrid_design_matrix_column_statistical_type_getter_test_suite() {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, 
        CGridDesignMatrixColStatsTypeGetter, 
        returns_mapped_statistical_data_type_if_overriding_type_is_undefined
    );

    add_test_with_context(suite, 
        CGridDesignMatrixColStatsTypeGetter, 
        returns_immediately_if_overriding_statistical_data_type_is_not_undefined
    );
    return suite;
}





