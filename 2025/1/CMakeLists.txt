cmake_minimum_required(VERSION 3.26)
project(MyProject VERSION 1.0 LANGUAGES CXX)


# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Separate executables for each part
add_executable(part_1
    src/1.cpp
)

add_executable(part_2
    src/1.cpp
)

target_compile_definitions(part_2 PRIVATE PART_2)

enable_testing()
add_test(NAME test_part_1a COMMAND part_1 "../inputs/a.txt")
set_property(TEST test_part_1a PROPERTY PASS_REGULAR_EXPRESSION "Password is: 3")

add_test(NAME test_part_1 COMMAND part_1 "../inputs/1.txt")
set_property(TEST test_part_1 PROPERTY PASS_REGULAR_EXPRESSION "Password is: 989")

add_test(NAME test_part_2b COMMAND part_2 "../inputs/b.txt")
set_property(TEST test_part_2b PROPERTY PASS_REGULAR_EXPRESSION "Password is: 10")

add_test(NAME test_part_2 COMMAND part_2 "../inputs/1.txt")
set_property(TEST test_part_2 PROPERTY PASS_REGULAR_EXPRESSION "Password is: 5941")
