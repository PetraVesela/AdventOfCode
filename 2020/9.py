''' Prefix sums '''
import itertools as it

PREAMBLE_LENGTH = 25

def main():
    with open("inputs/9.txt", 'r') as file:
        filedump = file.read().split('\n')

    numbers = [int(number) for number in filedump]

    for index, num in enumerate(numbers[PREAMBLE_LENGTH:]):
        options = list(it.combinations(numbers[index : index + PREAMBLE_LENGTH], 2))

        if num not in [sum(option) for option in options]:
            invalid_number = num
            numbers = numbers[:index] # cap the list for the second part
            print('Part 1: ', num)
            break

    # Find contiguous set that sums up to invalid_number
    prefix_sums = [sum(numbers[: i+1]) for i in range(len(numbers))]

    for start, start_num in enumerate(prefix_sums):
        for end in range(start+1, len(prefix_sums)):
            if prefix_sums[end] - start_num == invalid_number:
                our_slice = numbers[start+1 : end+1]
                print('Part 2: ', min(our_slice) + max(our_slice))
                break

if __name__ == "__main__":
    main()
