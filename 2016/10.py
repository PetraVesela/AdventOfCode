import re

COMPARE = {61, 17}

def add_to_dict(bots, index, element):
    try:
        bots[index].add(element)
    except KeyError:
        bots[index] = {element}
    return bots

def main():
    with open("inputs/10.txt", 'r') as file:
        data = file.read()

    lines = data.split('\n')

    #Initialize
    bots = dict()
    output = dict()

    # Iterate through a copy of the list:
    for line in lines[:]:
        numbers = re.findall(r'\d+', line)
        if len(numbers) == 2:
            bots = add_to_dict(bots, numbers[1], int(numbers[0]))
            lines.remove(line)

    # pass values:
    while lines:
        for line in lines[:]:
            numbers = re.findall(r'\d+', line)
            try:
                chips = list(bots[numbers[0]])
                if len(chips) == 2:

                    lower = chips[0] if chips[0] < chips[1] else chips[1]
                    higher = chips[1] if chips[1] > chips[0] else chips[0]

                    if line.split()[5] == 'bot':
                        bots = add_to_dict(bots, numbers[1], lower)
                    else:
                        output[numbers[1]] = lower

                    if line.split()[-2] == 'bot':
                        bots = add_to_dict(bots, numbers[2], higher)
                    else:
                        output[numbers[2]] = higher

                    lines.remove(line)
            except KeyError:
                pass
    # find the bot:
    for bot, chips in bots.items():
        if chips == COMPARE:
            print('Bot number: ', bot)
            break

    print('Output product: ', output['0']*output['1']*output['2'])

if __name__ == "__main__":
    main()
