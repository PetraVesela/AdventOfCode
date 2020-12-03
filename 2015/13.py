from itertools import permutations
from collections import defaultdict 

def default_value():
    return 0
    
def get_happiness(order, happiness_table):
    happiness = 0
    #select chunks:
    pairs = [order[i:i+2] for i in range(len(order)-1)]
    pairs.append((order[0], order[-1])) # connect the circle
    reversed_pairs = [pair[::-1] for pair in pairs]
    one_direction = sum(happiness_table[pair] for pair in pairs)
    other_direction = sum(happiness_table[pair] for pair in reversed_pairs)

    return one_direction + other_direction

def main():

    with open("inputs/13.txt") as file:
        data = file.read()
        
    data = data.split('\n')

    happiness = defaultdict(default_value)
    names = set()

    for line in data:
        words = line.split()
        names.add(words[0])
        key = (words[0], words[-1][:-1])
        if words[2] == 'gain':
            happiness[key] = int(words[3])
        else:
            happiness[key] = -int(words[3])

    perms = permutations(names)
    max_happiness = max([get_happiness(perm, happiness) for perm in perms])
    print('Without me: ', max_happiness)

    #2nd part:
    names.add('Petra')

    perms = permutations(names)
    max_happiness = max([get_happiness(perm, happiness) for perm in perms])
    print('With me: ', max_happiness)

if __name__ == '__main__':
    main()