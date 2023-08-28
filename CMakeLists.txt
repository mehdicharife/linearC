cmake_minimum_required(VERSION 2.8.12)

project(linearC LANGUAGES C CXX)
 
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set_source_files_properties(double_element_type.c PROPERTIES LANGUAGE C)

add_executable(test_double_element_type test_double_element_type.cpp)
target_link_libraries(test_double_element_type gtest_main)
add_test(test_double_element_type test_double_element_type.cpp)


add_executable(test_row_major_double_matrix test_row_major_double_matrix.cpp)
target_link_libraries(test_row_major_double_matrix gtest_main)
add_test(test_row_major_double_matrix test_row_major_double_matrix.cpp)
