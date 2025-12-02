cmake_minimum_required(VERSION 3.26)
project(MyProject VERSION 1.0 LANGUAGES CXX)


# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Separate executables for each part
add_executable(part_1
    src/2.cpp
)

add_executable(part_2
    src/2.cpp
)

target_compile_definitions(part_1 PRIVATE PART_1)

enable_testing()
add_test(NAME test_part_1a COMMAND part_1 "../inputs/a.txt")
set_property(TEST test_part_1a PROPERTY PASS_REGULAR_EXPRESSION "Sum of invalid IDs: 1227775554")

add_test(NAME test_part_1 COMMAND part_1 "../inputs/2.txt")
set_property(TEST test_part_1 PROPERTY PASS_REGULAR_EXPRESSION "Sum of invalid IDs: 41294979841")

add_test(NAME test_part_2a COMMAND part_2 "../inputs/a.txt")
set_property(TEST test_part_2a PROPERTY PASS_REGULAR_EXPRESSION "Sum of invalid IDs: 4174379265")

add_test(NAME test_part_2 COMMAND part_2 "../inputs/2.txt")
set_property(TEST test_part_2 PROPERTY PASS_REGULAR_EXPRESSION "Sum of invalid IDs: 66500947346")