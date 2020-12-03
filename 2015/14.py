import re

def get_distance(reindeer, seconds):

    velocity = reindeer[0]
    going = reindeer[1]
    resting = reindeer[2]

    cycles_completed = seconds // (resting + going)

    extra_seconds = seconds % (resting + going)
    is_waiting = extra_seconds > going

    if is_waiting:
        return (cycles_completed + 1) * velocity * going
    else:
        return cycles_completed * velocity * going + extra_seconds * velocity

def main():

    limit = 2503
    with open("inputs/14.txt") as file:
        data = file.read()

    data = data.split('\n')
    distances = []
    reindeer_numbers = []
    for line in data:
        reindeer = list(map(int, re.findall(r'\d+', line))) 
        reindeer_numbers.append(reindeer)
        distances.append(get_distance(reindeer, limit))

    print('1st round: ', max(distances))

    points = [0]*len(data)
    for second in range(1, limit+1):
        current_distances = [get_distance(reindeer, second) for reindeer in reindeer_numbers]

        lead = max(current_distances)
        indices = [i for i, dist in enumerate(current_distances) if dist == lead]
        for index in indices:
            points[index] = points[index] + 1

    print('2nd round: ', max(points))

if __name__ == '__main__':
    main()
