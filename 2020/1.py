import itertools as it
from functools import reduce

def main():
    with open("inputs/1.txt", 'r') as file:
        filedump = file.read()

    numbers = list(map(int, filedump.split('\n')))

    for c in list(it.combinations(numbers, 3)):
        if sum(c) == 2020:
            res = reduce((lambda x, y: x*y), c)
            print(res)


if __name__ == "__main__":
    main()
