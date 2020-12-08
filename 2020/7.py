import re

MY_BAG = 'shiny gold'

def contains_my_bag(bag, bag_dict):
    any_bag = []
    for bag_inside, _ in bag_dict[bag]:
        if bag_inside == MY_BAG:
            return True
        else:
            any_bag.append(contains_my_bag(bag_inside, bag_dict))
    return any(any_bag)

def how_many_bags_within(bag, bag_dict):
    total = 0
    for this_bag, num in bag_dict[bag]:
        total += num + num * how_many_bags_within(this_bag, bag_dict)

    return total


def main():
    with open("inputs/7.txt", 'r') as file:
        lines = file.read().split('\n')

    # parse into a dictionary:
    bag_dict = {}
    for line in lines:
        numbers = re.findall(r'\d+', line)
        words = line.split()

        contains = list()
        for num_id, number in enumerate(numbers):
            name_position = (num_id + 1)*4 + 1
            contains.append((' '.join(words[name_position : name_position + 2]), int(number)))

        bag_dict[' '.join(words[0:2])] = contains

    # Check for bags with my bag inside
    total = 0
    for bag in bag_dict:
        if contains_my_bag(bag, bag_dict):
            total += 1

    print("Part 1: ", total)

    # Check for bags inside my bag:
    bags_in_mine = bag_dict[MY_BAG]

    total = 0
    for bag in bags_in_mine:
        total += (bag[1] + bag[1] * how_many_bags_within(bag[0], bag_dict))
    print('Part 2: ', total)

if __name__ == "__main__":
    main()
