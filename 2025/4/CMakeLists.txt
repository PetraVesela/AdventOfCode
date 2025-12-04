cmake_minimum_required(VERSION 3.26)
project(MyProject VERSION 1.0 LANGUAGES CXX)


# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Separate executables for each part
add_executable(part_1_2
    src/4.cpp
)

enable_testing()
add_test(NAME test_part_1a COMMAND part_1_2 "../inputs/a.txt")
set_property(TEST test_part_1a PROPERTY PASS_REGULAR_EXPRESSION "Number of accessible rolls: 13")

add_test(NAME test_part_1 COMMAND part_1_2 "../inputs/4.txt")
set_property(TEST test_part_1 PROPERTY PASS_REGULAR_EXPRESSION "Number of accessible rolls: 1389")

add_test(NAME test_part_2a COMMAND part_1_2 "../inputs/a.txt")
set_property(TEST test_part_2a PROPERTY PASS_REGULAR_EXPRESSION "Number of removed rolls: 43")

add_test(NAME test_part_2 COMMAND part_1_2 "../inputs/4.txt")
set_property(TEST test_part_2 PROPERTY PASS_REGULAR_EXPRESSION "Number of removed rolls: 9000")