from itertools import combinations
from functools import reduce

# read the data
litres = 150

file  = open('inputs/17.txt', 'r')
containers = list( map( int,file.read().split()))

N = len(containers)
valid = 0
for n in range(1,N):
    res = combinations(containers, n)
    valid += len(list( filter(lambda x : x == litres , map(sum, res))))
    if valid != 0:
        break
print(valid)