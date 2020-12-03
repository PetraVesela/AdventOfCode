import re

my_sue = {
          'children': 3,
          'cats': 7,
          'samoyeds': 2,
          'pomeranians': 3,
          'akitas': 0,
          'vizslas': 0,
          'goldfish': 5,
          'trees': 3,
          'cars': 2,
          'perfumes': 1
}

def second_round(key, value):
    if key in ['cats', 'trees']:
        return int(value) <= my_sue.get(key)
    elif key in ['pomeranians', 'goldfish']:
        return int(value) >= my_sue.get(key)
    else:
        return int(value) != my_sue.get(key)



def main():

    with open("inputs/16.txt") as file:
        data = file.read().split('\n')


    for line in data:
        ctr = 0
        pairs = re.findall(r'[a-z]+: \d+', line)
        for pair in pairs:
            key, value = pair.split(': ')

            #condition = int(value) != my_sue.get(key)
            condition_not_obeyed = second_round(key, value)
            if condition_not_obeyed:
                break
            else:
                ctr = ctr+1
                continue
        if ctr == 3: # all 3 are correct
            print(line)

if __name__ == '__main__':
    main()
