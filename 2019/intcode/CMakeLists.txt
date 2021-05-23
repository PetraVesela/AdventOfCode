
cmake_minimum_required(VERSION 3.20)

project (intcode)

include_directories(
    ${CMAKE_SOURCE_DIR}/intcode_functions/
)
add_subdirectory(intcode_functions)

add_executable(day_2 2.c)

target_link_libraries(day_2 intcode)
