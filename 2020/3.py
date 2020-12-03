import numpy as np
import itertools as it

SLOPES = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]

def main():
    with open("inputs/3.txt", 'r') as file:
        filedump = file.read()

    filedump = filedump.replace('.', '0').replace('#', '1')

    lines = [list(line) for line in filedump.split('\n')]

    num_rows = len(lines)
    num_columns = len(lines[0])
    
    field = np.array(lines, dtype=int)

    prod = 1

    for slope in SLOPES:

        steps_down = list(range(0, num_rows, slope[1]))
        gen = it.count(0, slope[0])
        steps_right = list(next(gen) % num_columns for _ in range(num_rows))

        coord = list(zip(steps_down, steps_right))

        trees = [field[c] for c in coord]
        print(slope, ':', sum(trees))
        prod *= sum(trees)

    print('product:', prod)

if __name__ == "__main__":
    main()
