#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/double_element_type.h"

Test(double_element_type_test, singleton) {
    element_type* ptype1 = new_double_element_type();
    element_type* ptype2 = new_double_element_type();

    cr_expect(eq(ptr, ptype1, ptype2));
}


Test(double_element_type_test, pointer_addition) {
    double arr[5] = {1.0, 2.0, 5.0, 8.0, 6.0};
    int index = 2;

    element_type* dbtype = (element_type*) new_double_element_type();
    double* p = (double*) dbtype->pointer_addition(arr, index);

    cr_expect(eq(dbl, *p, arr[index]));
}

Test(double_element_type_test, addition) {
    double x = 5.0, y = 8.0, z;

    element_type* ptype = new_double_element_type();
    ptype->add(&x, &y, &z);

    cr_expect(eq(dbl, z, x + y));
}

Test(double_element_type_test, identity) {
    double x = 8.0, y;

    element_type* ptype = new_double_element_type();
    ptype->add(&x,
               ptype->get_addition_identity(),
               &y
    );

    cr_expect(eq(dbl, x, y));
}


Test(double_element_type_test, set) {
    double x;
    double y = 7.0;

    element_type* ptype = new_double_element_type();
    ptype->set(&x, &y);

    cr_expect(eq(dbl, x, y));
}

