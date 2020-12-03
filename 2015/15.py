import re
from itertools import permutations
import numpy as np

def get_score(weights, ingredients):
    vals = np.dot(weights, ingredients)
    if vals[-1] == 500:
        vals[vals < 0] = 0
        return np.prod(vals[:-1])
    else:
        return 0


def main():

    with open("inputs/15.txt") as file:
        data = file.read().split('\n')

    ingredients_numbers = []
    for line in data:
        ingredient = list(map(int, re.findall(r'-?\d+', line)))
        ingredients_numbers.append(ingredient)

    ingredients_numbers = np.array(ingredients_numbers)

    perms = permutations(list(range(98)), 4)
    result = 0
    for perm in perms:
        if sum(perm) == 100:
            score = get_score(np.array(perm), ingredients_numbers)
            if result < score:
                result = score
    print(result)



if __name__ == '__main__':
    main()
