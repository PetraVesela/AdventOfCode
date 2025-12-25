cmake_minimum_required(VERSION 3.26)
project(MyProject VERSION 1.0 LANGUAGES CXX)


# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Separate executables for each part
add_executable(part_1
    src/main.cpp
)

enable_testing()
add_test(NAME test_part_1a COMMAND part_1 "${CMAKE_SOURCE_DIR}/inputs/a.txt")
set_property(TEST test_part_1a PROPERTY PASS_REGULAR_EXPRESSION "Number of unique paths: 5.")

add_test(NAME test_part_1 COMMAND part_1 "${CMAKE_SOURCE_DIR}/inputs/full.txt")
set_property(TEST test_part_1 PROPERTY PASS_REGULAR_EXPRESSION "Number of unique paths: 733.")

add_test(NAME test_part_2b COMMAND part_1 "${CMAKE_SOURCE_DIR}/inputs/b.txt")
set_property(TEST test_part_2b PROPERTY PASS_REGULAR_EXPRESSION "Number of valid paths: 2.")

add_test(NAME test_part_2 COMMAND part_1 "${CMAKE_SOURCE_DIR}/inputs/full.txt")
set_property(TEST test_part_2 PROPERTY PASS_REGULAR_EXPRESSION "Number of valid paths: 290219757077250.")