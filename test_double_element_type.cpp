#include <gtest/gtest.h>

extern "C" {
    #include "double_element_type.c"
}


TEST(double_element_type_test, singleton) {
    element_type* ptype1 = new_double_element_type();
    element_type* ptype2 = new_double_element_type();

    ASSERT_EQ(ptype1, ptype2);
}


TEST(double_element_type_test, pointer_addition) {
    double arr[5] = {1.0, 2.0, 5.0, 8.0, 6.0};
    int index = 2;

    element_type* dbtype = (element_type*) new_double_element_type();
    double* p = (double*) dbtype->pointer_addition(arr, index);

    ASSERT_EQ(*p, arr[index]);
}

TEST(double_element_type_test, addition) {
    double x = 5.0, y = 8.0, z;

    element_type* ptype = new_double_element_type();
    ptype->add(&x, &y, &z);

    ASSERT_EQ(z, x + y);
}

TEST(double_element_type_test, identity) {
    double x = 8.0, y;

    element_type* ptype = new_double_element_type();
    ptype->add(&x,
               ptype->get_addition_identity(),
               &y
    );

    ASSERT_EQ(x, y);
}


TEST(double_element_type_test, set) {
    double x;
    double y = 7.0;

    element_type* ptype = new_double_element_type();
    ptype->set(&x, &y);

    ASSERT_EQ(x, y);
}

