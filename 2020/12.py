import math
STATES = ['E', 'N', 'W', 'S']

def rotate_point(pivot, point, angle):
    '''Rotate point a by b'''
    s = math.sin(math.radians(angle))
    c = math.cos(math.radians(angle))

    # translate point to origin
    point[0] -= pivot[0]
    point[1] -= pivot[1]

    # rotation matrix:
    # | COS  -SIN |
    # | SIN   COS |
    new_point = [0, 0]
    new_point[0] = point[0] * c - point[1] * s
    new_point[1] = point[0] * s + point[1] * c

    # translate point back
    new_point[0] += pivot[0]
    new_point[1] += pivot[1]
    return new_point


def move_ferry_1(instr, state):
    arg = int(instr[1:])
    current_direction = STATES.index(state[0])

    if instr[0] == 'F':
        instr = state[0]+str(arg)

    if instr[0] == 'N':
        state[1][0] += arg
    elif instr[0] == 'S':
        state[1][0] -= arg
    elif instr[0] == 'E':
        state[1][1] += arg
    elif instr[0] == 'W':
        state[1][1] -= arg
    elif instr[0] == 'L':
        new_index = (current_direction + (arg // 90)) % 4
        state[0] = STATES[new_index]
    elif instr[0] == 'R':
        new_index = (current_direction - (arg // 90)) % 4
        state[0] = STATES[new_index]

    return state

def move_ferry_2(instr, state):
    arg = int(instr[1:])
    waypoint = state[0]
    position = state[1]

    if instr[0] == 'F':
        rel = [waypoint[0] - position[0], waypoint[1] - position[1]]
        position[0] += arg * rel[0]
        position[1] += arg * rel[1]
        waypoint[0] = position[0] + rel[0]
        waypoint[1] = position[1] + rel[1]
    if instr[0] == 'N':
        waypoint[1] += arg
    elif instr[0] == 'S':
        waypoint[1] -= arg
    elif instr[0] == 'E':
        waypoint[0] += arg
    elif instr[0] == 'W':
        waypoint[0] -= arg
    elif instr[0] == 'L':
        waypoint = rotate_point(position, waypoint, arg)
    elif instr[0] == 'R':
        waypoint = rotate_point(position, waypoint, -arg)
    return [waypoint, position]

def main():
    with open("inputs/12.txt", 'r') as file:
        instructions = file.read().split('\n')

    state = ['E', [0, 0]]
    for instr in instructions:
        state = move_ferry_1(instr, state)
    print('Part 1: ', sum(map(abs, state[1])))

    state = [[10, 1], [0, 0]] #[waypoint, ship position]
    for instr in instructions:
        state = move_ferry_2(instr, state)

    print('Part 2: ', int(sum(map(abs, state[1]))))
if __name__ == "__main__":
    main()
