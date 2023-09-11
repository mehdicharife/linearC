#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include <string.h>
#include "../include/string_element_type.h"


element_type* (*type_factory)();

void setup(void) {
    type_factory = new_string_element_type;
}

TestSuite(string_element_type_test_suite, .init=setup);

Test(string_element_type_test_suite, singleton) {
    element_type* ptype1 = type_factory();
    element_type* ptype2 = type_factory();

    cr_expect(eq(ptr, ptype1, ptype2));
}



Test(string_element_type_test_suite, pointer_addition) {
    char* arr[5] = {"Foo", "Bar", "Lorem", "Ipsum"};
    size_t index = 2;

    element_type* dbtype = (element_type*) type_factory();
    char** p = dbtype->pointer_addition(arr, index);

    cr_expect(eq(str, *p, arr[index]));
}


Test(string_element_type_test_suite, identity) {
    element_type* ptype = type_factory();
    char expected[] = "haha";
    char* identity = *((char**) (ptype->get_addition_identity()));
    char actual[strlen(expected) + strlen(ptype->get_addition_identity()) + 1];

    strcpy(actual, expected);
    strcat(actual, identity);

    cr_expect(eq(str, actual, expected));
}


Test(string_element_type_test_suite, set) {
    char* actual = NULL;
    char* expected = "Foo";

    element_type* ptype = type_factory();
    ptype->set(&actual, &expected);

    cr_expect(eq(str, actual, expected));
}



Test(string_element_type_test_suite, matches_string) {
    element_type* ptype = type_factory();
    char str1[] = "\"Foo\"";
    char str2[] = "\"Bar\"";
    char str3[] = "Lorem";
    char str4[] = "2";
    char str5[] = "-1.2";
    
    cr_expect(ptype->matches_string(str1));
    cr_expect(ptype->matches_string(str2));   
    cr_expect(ptype->matches_string(str3));
    cr_expect(not(ptype->matches_string(str4)));
    cr_expect(not(ptype->matches_string(str5)));
}


Test(string_element_type_test_suite, are_equal) {
    element_type* ptype = type_factory();
    char* str00 = "Foo";
    char* str01 = "Foo";
    char* str10 = "\"Foo\"";
    char* str11 = "\"Foo\"";

    cr_expect(ptype->are_equal(&str00, &str01));
    cr_expect(ptype->are_equal(&str10, &str11));
    cr_expect(not(ptype->are_equal(&str00, &str10)));
}


Test(string_element_type_test_suite, gets_from_string) {
    element_type* ptype = type_factory();
   
    char* expected = strdup("Lorem");
    char** got = ptype->get_from_string(expected);
    cr_expect(ptype->are_equal(got, &expected));
    free(got);
}
