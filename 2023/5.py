#!/usr/bin/env python3
import argparse as ap
import matplotlib.pyplot as plt


class Mapping():
    def __init__(self, destination_start, source_start, range_length):
        self.destination_start = destination_start
        self.source_start = source_start
        self.range_length = range_length

    def is_mapped(self, value):
        if value >= self.source_start and value < self.source_start+self.range_length:
            return True
        return False

    def get_mapped_value(self, value):
        if self.is_mapped(value):
            offset = value - self.source_start
            return self.destination_start + offset
        return value

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        return f'{self.destination_start} - {self.source_start} - {self.rage_length}'

def get_location(val, category_mappings):
    # 7 types of mappings
    for category_mapping in [category_mappings[0]]:
        is_mapped = False
        for mapping in category_mapping:
            if mapping.is_mapped(val):
                is_mapped = True
                val = mapping.get_mapped_value(val)
                break
    return val


def parse_input(input_string, part):
    '''
    Parses the input file into a list of 7 distinct mappings,
    defined by an arbitrary number of mapping ranges.
    and a list of integer, seeds, in case part argument == 1, or a list of generators,
    in case the part argument == 2.
    '''
    lines = input_string.split('\n')
    seed_list = lines[0].split(':')[1].split()
    if part == 1:
        seeds = set(map(int, seed_list))
    else:
        seeds = []
        seeds_int = list(map(int, seed_list))
        for ind in range(0, len(seed_list), 2):
            start = seeds_int[ind]
            length = seeds_int[ind+1]
            seeds.append(range(start, start+length))

    category_mappings = []
    line_number = 1
    while line_number < len(lines):
        if "map" in lines[line_number]:
            this_mapping = []
            line_number += 1    
            while line_number < len(lines) and lines[line_number]:
                numbers = list(map(int, lines[line_number].split()))
                this_mapping.append(Mapping(numbers[0], numbers[1], numbers[2]))
                line_number +=1
            category_mappings.append(this_mapping)
        line_number += 1

    return seeds, category_mappings


def main(args):

    with open(args.input_file, encoding="utf-8") as file:
        seeds, category_mappings = parse_input(file.read(), args.part)

    # Find the location of all seeds:
    locations = []
    if args.part == 1:
        for seed in sorted(seeds):
            print(seed, " : ", get_location(seed, category_mappings))
            locations.append(get_location(seed, category_mappings))
    else:
        for seed_range in seeds:
            print(seed_range)
            for seed in seed_range:
                pass
    plt.plot(list(sorted(seeds)), locations)
    plt.show()
    print(f"Part {args.part}: {min(locations)}")


if __name__ == "__main__":
    parser = ap.ArgumentParser()
    parser.add_argument("input_file", help="The input file")
    parser.add_argument("part", help="Part 1 or 2", type=int)

    arguments = parser.parse_args()
    main(arguments)
