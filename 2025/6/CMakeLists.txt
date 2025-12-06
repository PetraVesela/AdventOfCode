cmake_minimum_required(VERSION 3.26)
project(MyProject VERSION 1.0 LANGUAGES CXX)


# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(part_1
    src/6.cpp
)

add_executable(part_2
    src/6.cpp
)
target_compile_definitions(part_1 PRIVATE PART_1)

enable_testing()
add_test(NAME test_part_1a COMMAND part_1 "../inputs/a.txt")
set_property(TEST test_part_1a PROPERTY PASS_REGULAR_EXPRESSION "Grand total is: 4277556.")

add_test(NAME test_part_1 COMMAND part_1 "../inputs/6.txt")
set_property(TEST test_part_1 PROPERTY PASS_REGULAR_EXPRESSION "Grand total is: 6503327062445.")

add_test(NAME test_part_2a COMMAND part_2 "../inputs/a.txt")
set_property(TEST test_part_2a PROPERTY PASS_REGULAR_EXPRESSION "Grand total is: 3263827.")

add_test(NAME test_part_2 COMMAND part_2 "../inputs/6.txt")
set_property(TEST test_part_2 PROPERTY PASS_REGULAR_EXPRESSION "Grand total is: 9640641878593.")