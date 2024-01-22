#!/usr/bin/env python3
import argparse as ap
import re

RE_D = re.compile(r'\d')
DIGITS_DICT = {
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
    "six": 6,
    "seven": 7,
    "eight": 8,
    "nine": 9
}


def get_digit(string, include_spelled):
    '''
    Returns the first literal or spelled out digit,
    or -1 if neither was found.
    '''
    digits = RE_D.search(string)
    if digits:
        return int(digits.group(0))
    if include_spelled:
        for digit in DIGITS_DICT:
            if string.find(digit) > -1:
                return DIGITS_DICT[digit]
    return -1

def get_first_digit(string, include_spelled):
    ind = 1
    while get_digit(string[0:ind], include_spelled) < 0:
        ind += 1
    return get_digit(string[0:ind], include_spelled)

def get_last_digit(string, include_spelled):
    ind = len(string)-2
    while get_digit(string[ind:], include_spelled) < 0:
        ind -= 1
    return get_digit(string[ind:], include_spelled)


def main(args):
    with open(args.input_file, encoding="utf-8") as file:
        sum_part_1 = 0
        for line in file:
            num = 10*get_first_digit(line, args.part == 2) + get_last_digit(line, args.part == 2)
            sum_part_1 += num

    print(f"Part {args.part}: ", sum_part_1)


if __name__ == "__main__":
    parser = ap.ArgumentParser()
    parser.add_argument("input_file", help="The input file")
    parser.add_argument("part", help="Part 1 or 2", type=int)

    arguments = parser.parse_args()
    main(arguments)
