cmake_minimum_required(VERSION 3.26)
project(MyProject VERSION 1.0 LANGUAGES CXX)


# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Separate executables for each part
add_executable(part_1
    src/5.cpp
)

enable_testing()
add_test(NAME test_part_1a COMMAND part_1 "../inputs/a.txt")
set_property(TEST test_part_1a PROPERTY PASS_REGULAR_EXPRESSION "Number of fresh ingredients: 3.")

add_test(NAME test_part_1 COMMAND part_1 "../inputs/5.txt")
set_property(TEST test_part_1 PROPERTY PASS_REGULAR_EXPRESSION "Number of fresh ingredients: 577.")

add_test(NAME test_part_2a COMMAND part_1 "../inputs/a.txt")
set_property(TEST test_part_2a PROPERTY PASS_REGULAR_EXPRESSION "Total number of fresh ingredients: 14.")

add_test(NAME test_part_2b COMMAND part_1 "../inputs/b.txt")
set_property(TEST test_part_2b PROPERTY PASS_REGULAR_EXPRESSION "Total number of fresh ingredients: 4.")

add_test(NAME test_part_2c COMMAND part_1 "../inputs/c.txt")
set_property(TEST test_part_2c PROPERTY PASS_REGULAR_EXPRESSION "Total number of fresh ingredients: 5.")

add_test(NAME test_part_2 COMMAND part_1 "../inputs/5.txt")
set_property(TEST test_part_2 PROPERTY PASS_REGULAR_EXPRESSION "Total number of fresh ingredients: 350513176552950.")