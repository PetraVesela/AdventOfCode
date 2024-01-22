#!/usr/bin/env python3
import argparse as ap
import math


class Schematic():
    def __init__(self, matrix):
        self.matrix = matrix
        self.numbers, self.number_map = self.get_all_numbers()
        self.gears = self.get_all_gears()

    def get_all_numbers(self):
        numbers = []
        number_map = {}
        for r, row in enumerate(self.matrix):
            c = 0
            while c < len(row):
                number = ""
                adj_indices = set()
                while row[c].isdigit() and c < len(row):
                    number += row[c]
                    adj_indices.update(get_neighbours(r,c))
                    c += 1
                if number:
                    numbers.append(Number(int(number), adj_indices, self.matrix))
                    for ind, _ in enumerate(number):
                        # For each digit of the number, store its coordinates:
                        number_map[(r, c-ind-1)] = int(number)
                c += 1
        return numbers, number_map

    def get_all_gears(self):
        gears = []
        for r, row in enumerate(self.matrix):
            for c, col in enumerate(row):
                if col == '*':
                    gears.append(Gear(get_neighbours(r,c), self.number_map))
        return gears


class Number():
    def __init__(self, num, adj_ind, matrix):
        self.num = num
        self.adj_ind = adj_ind
        self.is_valid = self.touches_a_symbol(matrix)

    def __str__(self):
        return str(self.num)

    def __repr__(self):
        return self.__str__()

    def touches_a_symbol(self, matrix):
        for adj in self.adj_ind:
            try:
                char = matrix[adj[0]][adj[1]]
                if char.isdigit() or char == '.' or char.isspace():
                    continue
                return True
            except IndexError:
                continue
        return False


class Gear():
    def __init__(self, adj_ind, number_map):
        self.adj_ind = adj_ind
        self.neighbouring_numbers = self.get_neighbouring_numbers(number_map)
        self.is_valid = len(self.neighbouring_numbers) == 2

    def get_neighbouring_numbers(self, number_map):
        neighbouring_numbers = set()

        for adj in self.adj_ind:
            try:
                num = number_map[(adj[0], adj[1])]
                neighbouring_numbers.add(num)
            except KeyError:
                continue

        return neighbouring_numbers

    def get_ratio(self):
        if self.is_valid:
            return math.prod(self.neighbouring_numbers)
        return 0


def get_neighbours(r, c):
    neighbours = [(r-1, c-1), (r-1, c), (r-1, c+1),
                  (r,   c-1),           (r,   c+1),
                  (r+1, c-1), (r+1, c), (r+1, c+1)]
    return neighbours


def main(args):
    matrix = []
    with open(args.input_file, encoding="utf-8") as file:
        for line in file:
            matrix.append([*line])

    schematic = Schematic(matrix)

    # Part 1
    sum_of_numbers = 0

    for num in schematic.numbers:
        if num.is_valid:
            sum_of_numbers += num.num

    print("Part 1:", sum_of_numbers)

    # Part 2:
    sum_of_gears = 0
    for gear in schematic.gears:
        if gear.is_valid:
            sum_of_gears += gear.get_ratio()

    print("Part 1:", sum_of_gears)


if __name__ == "__main__":
    parser = ap.ArgumentParser()
    parser.add_argument("input_file", help="The input file")

    arguments = parser.parse_args()
    main(arguments)
