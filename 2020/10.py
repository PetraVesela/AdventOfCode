''' Dynamic programming? '''
from time import time

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
    t0 = time()
    total = 1
    index = 0
    
    num_chunks = 4
    for ind in range(num_chunks):
        chunk = len(adapters)/num_chunks
        total_1 *= follow_path(index, chunk, total)
    t1 = time()
    print(t1-t0)
    print('Part 2: ', total_1*total_2)


if __name__ == "__main__":
    main()
