def decompress_inefficient(data):
    '''Solves single depth level by expanding the string'''
    lst = list(data)
    decompressed = []

    position = 0
    while position < len(lst):

        if lst[position] == '(':
            start = position + 1
            while (lst[position]) != ')':
                position += 1
            end = position


            instruction = ''.join(lst[start:end])
            length = int(instruction.split('x')[0])
            repeated = int(instruction.split('x')[1])
            buffer = repeated * lst[position+1 : position+1 + length]

            decompressed.extend(buffer)
            position += length + 1
        else:
            decompressed.append(lst[position])
            position += 1
    return ''.join(decompressed)


def decompress_efficient(data):
    '''Returns recursively the length of total decompressed string'''
    lst = list(data)
    position = 0
    total_length = 0

    while position < len(lst):
        if lst[position] == '(':
            start = position + 1
            while (lst[position]) != ')':
                position += 1
            end = position

            instruction = ''.join(lst[start:end])
            length = int(instruction.split('x')[0])
            repeated = int(instruction.split('x')[1])
            substring = ''.join(lst[position+1 : position+1 + length])

            if '(' in substring: # dive deeper
                total_length += repeated * decompress_efficient(substring)
            else:
                total_length += repeated * len(substring)

            position += (length + 1)
        else:
            total_length += 1 #uncompressed letter
            position += 1
    return total_length

def main():
    with open("inputs/9.txt", 'r') as file:
        data = file.read()

    print("Part 1 : ", len(decompress_inefficient(data)))

    total_length = decompress_efficient(data)
    print("Part 2 : ", total_length)

if __name__ == "__main__":
    main()
