cmake_minimum_required(VERSION 3.22)
project(MyProject VERSION 1.0 LANGUAGES CXX)


# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Separate executables for each part
add_executable(part_1
    src/main.cpp
)
add_executable(part_1_short
    src/main.cpp
)

add_executable(part_2
    src/main.cpp
)

target_compile_definitions(part_2 PRIVATE PART_2)
target_compile_definitions(part_1_short PRIVATE SHORT_INPUT)

enable_testing()
add_test(NAME test_part_1a COMMAND part_1_short "${CMAKE_SOURCE_DIR}/inputs/a.txt")
set_property(TEST test_part_1a PROPERTY PASS_REGULAR_EXPRESSION "Product of circuit sizes: 40.")

add_test(NAME test_part_1 COMMAND part_1 "${CMAKE_SOURCE_DIR}/inputs/full.txt")
set_property(TEST test_part_1 PROPERTY PASS_REGULAR_EXPRESSION "Product of circuit sizes: 57970.")

add_test(NAME test_part_2a COMMAND part_1 "${CMAKE_SOURCE_DIR}/inputs/a.txt")
set_property(TEST test_part_2a PROPERTY PASS_REGULAR_EXPRESSION "Product of X coordinates: 25272.")

add_test(NAME test_part_2 COMMAND part_2 "${CMAKE_SOURCE_DIR}/inputs/full.txt")
set_property(TEST test_part_2 PROPERTY PASS_REGULAR_EXPRESSION "Product of X coordinates: 8520040659.")