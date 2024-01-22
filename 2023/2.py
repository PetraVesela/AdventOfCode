#!/usr/bin/env python3
import argparse as ap
import re

class Bag:
    def __init__(self, red=0, green=0, blue=0):
        self.r = red
        self.g = green
        self.b = blue

    def is_valid(self):
        return  self.r <= 12 and self.g <= 13 and self.b <= 14

    def get_power(self):
        return self.r * self.g * self.b


def verify_game(draws):
    for draw in draws:
        for colour in draw.split(','):
            num = int(re.findall(r'\d+', colour)[0])
            if "red" in colour:
                is_valid = Bag(red=num).is_valid()
            elif "green" in colour:
                is_valid = Bag(green=num).is_valid()
            elif "blue" in colour:
                is_valid = Bag(blue=num).is_valid()
            if not is_valid:
                return False
    return True


def get_minimum_bag(draws):
    min_red = 0
    min_green = 0
    min_blue = 0
    for draw in draws:
        for colour in draw.split(','):
            num = int(re.findall(r'\d+', colour)[0])
            if "red" in colour:
                min_red = num if num > min_red else min_red
            elif "green" in colour:
                min_green = num if num > min_green else min_green
            elif "blue" in colour:
                min_blue = num if num > min_blue else min_blue

    return Bag(red=min_red, blue=min_blue, green=min_green)

def main(args):
    with open(args.input_file, encoding="utf-8") as file:
        sum_id = 0
        sum_power = 0
        for line in file:
            game_id = int(line.split(':')[0].split()[1])
            draws = line.split(':')[1].split(';')
            if verify_game(draws):
                sum_id += game_id

            sum_power += get_minimum_bag(draws).get_power()

    print("Part 1: ", sum_id)
    print("Part 2: ", sum_power)

if __name__ == "__main__":
    parser = ap.ArgumentParser()
    parser.add_argument("input_file", help="The input file")

    arguments = parser.parse_args()
    main(arguments)
