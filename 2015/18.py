''' For part 1/2 toggle lines 37/38'''
import numpy as np


def get_neighbours(r, c, field_size):
    neighbours = [(r-1, c-1), (r-1, c), (r-1, c+1),
                  (r,   c-1),           (r,   c+1),
                  (r+1, c-1), (r+1, c), (r+1, c+1)]

    return [nb for nb in neighbours if not set(nb).intersection({-1, field_size})]

def toggle(element, neighbours_on, corner=False):
    if not corner:
        if element:
            return neighbours_on in [2, 3]
        return neighbours_on == 3
    return True

def main():
    with open("inputs/18.txt", 'r') as file:
        data = file.read()

    data = data.replace('#', '1').replace('.', '0')
    lines = [list(line) for line in data.split('\n')]
    field_size = len(lines)
    corners = [(0,0),             (0, field_size-1),
               (field_size-1, 0), (field_size-1, field_size-1)]
    field = np.array(lines, dtype=int)

    for _ in range(100):
        new_field = np.zeros(np.shape(field), dtype=int)
        for row in range(field_size):
            for column in range(field_size):
                neighbours = get_neighbours(row, column, field_size)
                neighbours_on = sum([field[nb] for nb in neighbours if field[nb]])
                corner = (row, column) in corners
                #new_field[row, column] = toggle(field[row, column], neighbours_on)
                new_field[row, column] = toggle(field[row, column], neighbours_on, corner)
        field = new_field
    print('Part 1:', sum(sum(field)))


if __name__ == "__main__":
    main()
