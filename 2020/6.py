def main():
    with open("inputs/6.txt", 'r') as file:
        filedump = file.read()

    groups = filedump.split('\n\n')

    total_part1 = 0
    total_part2 = 0
    for group in groups:
        combined = set(group.replace('\n', ''))
        total_part1 += len(combined)

        people = [set(person) for person in group.split('\n')]
        common = set.intersection(*people)
        total_part2 += len(common)

    print('Part 1:', total_part1)
    print('Part 2:', total_part2)


if __name__ == "__main__":
    main()
