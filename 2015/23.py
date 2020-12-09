START_VALUE = 1

def main():
    with open("inputs/23.txt", 'r') as file:
        instructions = file.read().split('\n')

    ctr = 0
    registers = {
        'a' : START_VALUE,
        'b' : 0
    }
    while ctr < len(instructions):
        # head unfolding
        opcode, *args = instructions[ctr].split()

        if ',' in args[0]: #strip ','
            args[0] = args[0][0]

        if opcode == 'hlf':
            registers[args[0]] //= 2
            ctr += 1
        elif opcode == 'tpl':
            registers[args[0]] *= 3
            ctr += 1
        elif opcode == 'inc':
            registers[args[0]] += 1
            ctr += 1
        elif opcode == 'jmp':
            ctr += int(args[0])
        elif opcode == 'jie' and not registers[args[0]] % 2:
            ctr += int(args[1])
        elif opcode == 'jio' and registers[args[0]] == 1:
            ctr += int(args[1])
        else:
            ctr += 1

    print('Part 1: ', registers['b'])

if __name__ == "__main__":
    main()
