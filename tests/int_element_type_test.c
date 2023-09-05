#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include "../include/int_element_type.h"


element_type* (*type_factory)();

void setup(void) {
    type_factory = new_int_element_type;
}

TestSuite(int_element_type_test_suite, .init=setup);

Test(int_element_type_test_suite, singleton) {
    element_type* ptype1 = type_factory();
    element_type* ptype2 = type_factory();

    cr_expect(eq(ptr, ptype1, ptype2));
}


Test(int_element_type_test_suite, pointer_addition) {
    int arr[5] = {1, 2, 5, 8, 6};
    int index = 2;

    element_type* dbtype = (element_type*) type_factory();
    int* p = (int*) dbtype->pointer_addition(arr, index);

    cr_expect(eq(int, *p, arr[index]));
}

Test(int_element_type_test_suite, addition) {
    int x = 5, y = 8, z;

    element_type* ptype = type_factory();
    ptype->add(&x, &y, &z);

    cr_expect(eq(int, z, x + y));
}

Test(int_element_type_test_suite, identity) {
    int x = 8, y;

    element_type* ptype = type_factory();
    ptype->add(&x,
               ptype->get_addition_identity(),
               &y
    );

    cr_expect(eq(int, x, y));
}


Test(int_element_type_test_suite, set) {
    int x;
    int y = 7;

    element_type* ptype = type_factory();
    ptype->set(&x, &y);

    cr_expect(eq(int, x, y));
}


Test(int_element_type_test_suite, matches_string) {
    element_type* ptype = type_factory();
    char str1[] = "5";
    char str2[] = "0";
    char str3[] = "not_a_int";
    char str4[] = "2.6";
    
    cr_expect(ptype->matches_string(str1));
    cr_expect(ptype->matches_string(str2));   
    cr_expect(not (ptype->matches_string(str3)));
    cr_expect(not (ptype->matches_string(str4)));
}


Test(int_element_type_test_suite, get_value_from_string) {
    element_type* ptype = type_factory();
    char* int_as_str = "5";
    void* got = ptype->get_from_string(int_as_str);
    int expected = 5;

    cr_expect(ptype->are_equal(got, &expected));
}