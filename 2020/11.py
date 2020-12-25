'''
Get slope by using atan2 - works on all four quadrants
Refactor
'''

import math
import numpy as np

# L => 0 => free seat
# . => 2 => floor
# # => 1 => occupied

def get_neighbours(r, c, field, floor_coords, extended=0):
    field_size = (np.shape(field))
    neighbours = [(r-1, c-1), (r-1, c), (r-1, c+1),
                  (r,   c-1),           (r,   c+1),
                  (r+1, c-1), (r+1, c), (r+1, c+1)]

    if not extended:
        return [nb for nb in neighbours if nb[0] not in {-1, field_size[0]}
                and nb[1] not in {-1, field_size[1]}
                and nb not in floor_coords]

    neighbours_incl_floor = [nb for nb in neighbours if nb[0] not in {-1, field_size[0]}
                             and nb[1] not in {-1, field_size[1]}]

    for neighbour in neighbours_incl_floor[:]:
        if field[neighbour] == 2: # if it is floor, check also behind it
            slope = math.atan2(neighbour[0] - r, neighbour[1] - c)
            other_in_this_direction = list()

            for row in range(field_size[0]):
                for column in range(field_size[1]):
                    if math.atan2(row - r, column - c) == slope:
                        if (row != r or column != c):
                            other_in_this_direction.append((row, column))
                            seats = [field[seat] for seat in other_in_this_direction]

            # Sort in direction of view:
            if neighbour > other_in_this_direction[0]:
                other_in_this_direction.sort(reverse=True)
                seats = [field[seat] for seat in other_in_this_direction]
            # replace the floor by next visible seat - empty or occupied
            for ind, seat in enumerate(seats):
                if seat in {0, 1}:
                    neighbours_incl_floor.remove(neighbour)
                    neighbours_incl_floor.append(other_in_this_direction[ind])
                    break

    return neighbours_incl_floor


def run_iteration_1(field, floor_coords, field_size):
    new_field = np.zeros(np.shape(field), dtype=int)
    for row in range(field_size[0]):
        for column in range(field_size[1]):
            neighbours = get_neighbours(row, column, field_size, floor_coords)

            neighbours_occupied = sum([field[nb] for nb in neighbours if field[nb]])


            if not field[row][column] and neighbours_occupied == 0:
                new_field[row][column] = 1
            elif field[row][column] == 1 and neighbours_occupied > 3:
                new_field[row][column] = 0
            else:
                new_field[row][column] = field[row][column]
    return new_field


def run_iteration_2(field, floor_coords, field_size):
    new_field = np.zeros(np.shape(field), dtype=int)
    for row in range(field_size[0]):
        for column in range(field_size[1]):
            neighbours = get_neighbours(row, column, field, floor_coords, extended=1)
            neighbours_occupied = sum([field[nb] for nb in neighbours if field[nb] == 1])

            if not field[row][column] and neighbours_occupied == 0:
                new_field[row][column] = 1
            elif field[row][column] == 1 and neighbours_occupied > 4:
                new_field[row][column] = 0
            else:
                new_field[row][column] = field[row][column]
    return new_field


def main():
    with open("inputs/11.txt", 'r') as file:
        filedump = file.read().replace('L', '0').replace('.', '2')

    lines = [list(line) for line in filedump.split('\n')]

    field = np.array(lines, dtype=int)
    field_size = (np.shape(field))

    # get excluded floor coordinates:
    floor_coords = []
    for row in range(field_size[0]):
        for column in range(field_size[1]):
            if field[row][column] == 2:
                floor_coords.append((row, column))

    new_field = np.zeros(np.shape(field), dtype=int)
    while (new_field != field).any():
        if sum(sum(new_field)): # except for the first time
            field = np.array(new_field, copy=True)
        new_field = run_iteration_1(field, floor_coords, field_size)

    part_1 = len(list(new_field[new_field == 1]))
    print('Part 1: ', part_1)
    iteration = 0
    while (new_field != field).any():
        if sum(sum(new_field)): # except for the first time
            field = np.array(new_field, copy=True)
        new_field = run_iteration_2(field, floor_coords, field_size)
        print(iteration)
        iteration += 1
        print(new_field)

    part_2 = len(list(new_field[new_field == 1]))
    print('Part 2: ', part_2)

if __name__ == "__main__":
    main()
