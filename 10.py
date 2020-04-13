from itertools import groupby   

sequence = '1321131112';

for n in range(51):
    print(n, len(sequence))

    temp_sequence = [list(g) for k, g in groupby(sequence)]
    sequence = ''.join([str(len(item))+str(item[0]) for item in temp_sequence])
