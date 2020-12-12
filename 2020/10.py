''' Dynamic programming? '''

def get_possible_steps(adapters, index):
    current = adapters[index]
    theoretically = {current+1, current+2, current+3}
    return set(adapters).intersection(theoretically)

def follow_path(index, adapters, total):
    while index != len(adapters) - 1:
        next_steps = get_possible_steps(adapters, index)
        if len(next_steps) == 1:
            index += 1
            continue
        else:
            for next_step in next_steps:
                index = adapters.index(next_step)
                total = follow_path(index, adapters, total)
            return total
    return total+1 # when arrived till the end

def main():
    with open("inputs/10.txt", 'r') as file:
        filedump = file.read().split('\n')

    adapters = [int(num) for num in filedump]
    adapters.append(0) # outlet
    adapters = sorted(adapters)
    adapters.append(adapters[-1] + 3) #built_in

    # get diff list:
    diff_list = []
    for x, y in zip(adapters[0:], adapters[1:]):
        diff_list.append(y-x)

    print('Part 1: ', diff_list.count(1) * diff_list.count(3))
    total = 0
    index = 0
    first_half = adapters[:44]
    second_half = adapters[44:]

    total_1 = follow_path(index, first_half, total)
    total_2 = follow_path(index, second_half, total)
    print('Part 2: ', total_1*total_2)


if __name__ == "__main__":
    main()
