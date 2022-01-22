"""
numpy.ndenumerate
"""
import numpy as np

def get_helper_matrix(mat):
    res = np.empty_like(mat, dtype=object)
    for (x, y), value in np.ndenumerate(mat):
        res[x, y] = value[0]
    return res


def manhattan_distance(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def main():

    # Read cell coordinates
    with open("inputs/6.txt", 'r') as file:
        filedump = file.read().split('\n')

    coord = [(int(nums.split(', ')[0]), int(nums.split(', ')[1])) for nums in filedump]

    # Find min and max coord in each dimension
    coord_row = [c[0] for c in coord]
    coord_col = [c[1] for c in coord]

    # Create helper matrix
    mat = np.empty((max(coord_row)+1, max(coord_col)+1), dtype=object)

    for ind, c in enumerate(coord):
        for (row, col), value in np.ndenumerate(mat):
            if mat[row, col] is None or manhattan_distance(c, (row, col)) < value[1]:
                mat[row, col] = (ind, manhattan_distance(c, (row, col)))
            elif manhattan_distance(c, (row, col)) == value[1]:
                mat[row, col] = (-1, manhattan_distance(c, (row, col)))

    helper = get_helper_matrix(mat)

    # Get indices of infinite areas as set of all indices at the matrix edges
    infinite_ind = set([*helper[0, :], *helper[:, 0], *helper[-1, :], *helper[:, -1]])

    # the rest are finite areas:
    all_ind = set(range(-1, len(filedump)))
    finite_ind = all_ind - infinite_ind

    biggest_finite = -1
    for ind in finite_ind:
        biggest_finite = max(biggest_finite, np.count_nonzero(helper == ind))

    print(f"Part 1: {biggest_finite}")

    # Part 2
    limit = 10000
    close_region_size = 0
    for (row, col), value in np.ndenumerate(mat):
        all_distances = [manhattan_distance((row, col), point) for point in coord]
        if sum(all_distances) < limit:
            close_region_size += 1

    print(f"Part 2: {close_region_size}")


if __name__ == "__main__":
    main()
