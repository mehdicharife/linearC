#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include "../include/double_element_type.h"


element_type* (*type_factory)();

void setup(void) {
    type_factory = new_double_element_type;
}

TestSuite(double_element_type_test_suite, .init=setup);

Test(double_element_type_test_suite, singleton) {
    element_type* ptype1 = type_factory();
    element_type* ptype2 = type_factory();

    cr_expect(eq(ptr, ptype1, ptype2));
}


Test(double_element_type_test_suite, pointer_addition) {
    double arr[5] = {1.0, 2.0, 5.0, 8.0, 6.0};
    int index = 2;

    element_type* dbtype = (element_type*) type_factory();
    double* p = (double*) dbtype->pointer_addition(arr, index);

    cr_expect(eq(dbl, *p, arr[index]));
}

Test(double_element_type_test_suite, addition) {
    double x = 5.0, y = 8.0, z;

    element_type* ptype = type_factory();
    ptype->add(&x, &y, &z);

    cr_expect(eq(dbl, z, x + y));
}

Test(double_element_type_test_suite, identity) {
    double x = 8.0, y;

    element_type* ptype = type_factory();
    ptype->add(&x,
               ptype->get_addition_identity(),
               &y
    );

    cr_expect(eq(dbl, x, y));
}


Test(double_element_type_test_suite, set) {
    double x;
    double y = 7.0;

    element_type* ptype = type_factory();
    ptype->set(&x, &y);

    cr_expect(eq(dbl, x, y));
}


Test(double_element_type_test_suite, matches_string) {
    element_type* ptype = type_factory();
    char str1[] = "5.2";
    char str2[] = ".5";
    char str3[] = "not_a_double";
    char str4[] = "2";
    char str5[] = "-1.2";
    
    cr_expect(ptype->matches_string(str1));
    cr_expect(ptype->matches_string(str2));   
    cr_expect(not (ptype->matches_string(str3)));
    cr_expect(not (ptype->matches_string(str4)));
    cr_expect(ptype->matches_string(str5));
}


