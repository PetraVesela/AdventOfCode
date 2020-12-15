''' For Part 1, change LIMIT to 2020'''

INPUT = [0, 20, 7, 16, 1, 18, 15]
LIMIT = 30000000

def main():
    last_seen = dict()

    #initialize
    for ind, num in enumerate(INPUT):
        last_seen[num] = [ind+1]
    last_spoken = INPUT[-1]

    for ind in range(len(INPUT)+1, LIMIT + 1):
        if(len(last_seen[last_spoken])) == 1: #last_spoken appeared the first time:
            last_spoken = 0
        else:# last_spoken appeared at least twice
             last_spoken = last_seen[last_spoken][1] - last_seen[last_spoken][0]
        try:
            if len(last_seen[last_spoken]) == 2:
                last_seen[last_spoken].pop(0)
            last_seen[last_spoken].append(ind)
        except KeyError:
            last_seen[last_spoken] = [ind]
    print(last_spoken)

if __name__ == "__main__":
    main()
