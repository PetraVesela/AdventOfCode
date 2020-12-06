'''Context-free grammar: https://en.wikipedia.org/wiki/Context-free_grammar'''
import random

def replace_kth_occurrence(string, substring_old, substring_new, k):
    start_index = -1
    for i in range(1, k+1): # i = 1,2,3 k = 3

        start_index = string.find(substring_old, start_index + 1)

        if start_index == -1 and i < k: #less than k matches
            return start_index

        if start_index != -1 and i == k:
            res = string[:start_index] + substring_new + string[start_index + len(substring_old) :]
            return res

    return -1

def main():

    with open("inputs/19.txt") as file:
        data = file.read().split('\n')

    input_string = data[-1]
    available_subs = [line.split(' => ') for line in data[:-2]]
    substitutions = set()

    for subs in available_subs:

        k = 1
        while True:
            new_string = replace_kth_occurrence(input_string, subs[0], subs[1], k)
            if new_string == -1:
                break
            substitutions.add(new_string)
            k += 1
    print("Distinct molecules : ", len(substitutions))

    # Fold up the molecule into a single electron:

    iteration = 0
    current = 0

    while input_string != 'e':
        
        to_replace = input_string.count(available_subs[current][1])
        if to_replace:
            input_string = input_string.replace(available_subs[current][1],
                                                available_subs[current][0])
            iteration += to_replace

        else:
            current += 1

        if current == len(available_subs): #wrap around
            current = 0
        if input_string == 'NRnBSiRnCaRnFArYFArFArF': # dead end
            # start all over:
            input_string = data[-1]
            random.shuffle(available_subs)
            iteration = 0
    print("Number of substitutions: ", iteration)

if __name__ == '__main__':
    main()
