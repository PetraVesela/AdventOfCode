#!/usr/bin/env python3
import argparse as ap
from collections import defaultdict


def main(args):

    with open(args.input_file, encoding="utf-8") as file:
        total_points = 0
        scratchcards = []
        num_scratchcard_copies = defaultdict(lambda: 1)
        for card_num, card_line in enumerate(file):
            winning_numbers_str, my_numbers_str = card_line.split(':')[1].split('|')
            winning_numbers = set(map(int, winning_numbers_str.split()))
            my_numbers = set(map(int, my_numbers_str.split()))
            common_numbers = my_numbers.intersection(winning_numbers)
            scratchcards.append((winning_numbers, my_numbers))

            # Part 1:
            if common_numbers:
                total_points += 2**(len(common_numbers)-1)

            # Part 2:
            for _ in range(num_scratchcard_copies[card_num]):
                for ind, _ in enumerate(common_numbers):
                    num_scratchcard_copies[card_num + ind + 1] += 1

        # Count all the scratchcards
        total_num_scratchcards = 0
        for card in num_scratchcard_copies:
            total_num_scratchcards += num_scratchcard_copies[card]

        print("Part 1: ", total_points)
        print("Part 2: ", total_num_scratchcards)


if __name__ == "__main__":
    parser = ap.ArgumentParser()
    parser.add_argument("input_file", help="The input file")
    arguments = parser.parse_args()
    main(arguments)
