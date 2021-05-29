cmake_minimum_required(VERSION 3.20)

project (intcode)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/
)

enable_testing()
add_subdirectory(lib)

add_subdirectory(days)
add_subdirectory(tst)
