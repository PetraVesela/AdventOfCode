import numpy as np

# read the data
file  = open('inputs/6.txt', 'r')

# define the grid
grid_part1 = np.zeros((1000,1000), dtype=int)
grid_part2 = np.zeros((1000,1000), dtype=int)
line = file.readline()

while line: #parse into coordinates
    words = line.split(' ')
    if words[-1] == '\n':
        numbers = [words[-3], words[-1][:-1]]
    else:
        numbers = [words[-3], words[-1]]
    coords = [n.split(',') for n in numbers]
    flattened = [n for sublist in coords for n in sublist]
    coords = list( map( int, flattened))
    indices = (slice(coords[0],coords[2]+1),slice(coords[1],coords[3]+1))
    
    if words[1] == 'on':
        grid_part1[indices] = 1
        grid_part2[indices] += 1
    if words[1] == 'off':
        grid_part1[indices] = 0
        grid_part2[indices] -= 1
        grid_part2[grid_part2<0] = 0
    if words[0] == 'toggle':
        grid_part1[indices] = np.logical_not( grid_part1[indices])
        grid_part2[indices] += 2
        
    line = file.readline()
    
print("Part 1: {}".format( sum( sum(grid_part1))))
print("Part 2: {}".format( sum( sum(grid_part2))))
file.close()
