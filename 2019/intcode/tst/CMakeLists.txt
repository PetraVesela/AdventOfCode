# Day 2 

add_test(NAME Day_2_regression COMMAND day_2 ../../../inputs/2.txt 0)

# Day 5

add_test(NAME Day_5_throughput COMMAND day_5 ../../../inputs/5_throughput.txt 42)

set_tests_properties(
    Day_5_throughput PROPERTIES
    PASS_REGULAR_EXPRESSION "42"
)

add_test(NAME Day_5_if_8_shorter COMMAND day_5 ../../../inputs/5_if_8_shorter.txt 8)
add_test(NAME Day_5_if_lt_8_shorter COMMAND day_5 ../../../inputs/5_if_lt_8_shorter.txt 8)
add_test(NAME Day_5_if_not_8_shorter COMMAND day_5 ../../../inputs/5_if_8_shorter.txt 10)

set_tests_properties(
    Day_5_if_8_shorter PROPERTIES
    PASS_REGULAR_EXPRESSION "1"
)


add_test(NAME Day_5_jump_test_immediate COMMAND day_5 ../../../inputs/5_jump_test_immediate.txt 0)
add_test(NAME Day_5_jump_test_position COMMAND day_5 ../../../inputs/5_jump_test_position.txt 0)

add_test(NAME Day_5_if_8_larger COMMAND day_5 ../../../inputs/5_if_8_larger.txt 8)

set_tests_properties(
    Day_5_if_8_larger PROPERTIES
    PASS_REGULAR_EXPRESSION "1000"
)

add_test(NAME Day_5_greater_than_8_larger COMMAND day_5 ../../../inputs/5_if_8_larger.txt 10)

set_tests_properties(
    Day_5_greater_than_8_larger PROPERTIES
    PASS_REGULAR_EXPRESSION "1001"
)

add_test(NAME Day_5_regression_part_1 COMMAND day_5 ../../../inputs/5.txt 1)
set_tests_properties(
    Day_5_regression_part_1 PROPERTIES
    PASS_REGULAR_EXPRESSION "11193703"
)
add_test(NAME Day_5_regression_part_2 COMMAND day_5 ../../../inputs/5.txt 5)
set_tests_properties(
    Day_5_regression_part_2 PROPERTIES
    PASS_REGULAR_EXPRESSION "12410607"
)

# Day 7
add_test(NAME Day_7_shorter_1 COMMAND day_7 ../../../inputs/7_shorter_1.txt)
set_tests_properties(
    Day_7_shorter_1 PROPERTIES
    PASS_REGULAR_EXPRESSION "4321"
)

# Day 7
add_test(NAME Day_7 COMMAND day_7 ../../../inputs/7.txt)
