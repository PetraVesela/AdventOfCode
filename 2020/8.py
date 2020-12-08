def execute(opcode, accumulator, value, ctr):
    if opcode == 'acc':
        accumulator += value
        ctr += 1
    elif opcode == 'jmp':
        ctr += value
    elif opcode == 'nop':
        ctr += 1
    return accumulator, ctr

def run_program(instructions):
    '''
    Run the instructions and break if either:
        a) one execution should be executed twice (i.e. infinite loop)
        b) last instruction is successfully executed
    '''
    accumulator = 0
    executed = set()

    ctr = 0
    while instructions:
        try:
            instr = instructions[ctr]
        except IndexError:
            break # b)
        opcode, value = instr.split()
        value = int(value)

        if ctr not in executed:
            executed.add(ctr)
        else:
            break # a)

        accumulator, ctr = execute(opcode, accumulator, value, ctr)
    did_the_whole_program_run = ctr == len(instructions)

    return did_the_whole_program_run, accumulator


def main():
    with open("inputs/8.txt", 'r') as file:
        instructions = file.read().split('\n')

    _, accumulator = run_program(instructions)

    print('Part 1: ', accumulator)

    for instr in instructions[:]:
        if instr[0:3] == 'jmp': #opcode
            new_instr = instr.replace('jmp', 'nop')
            replaced = '\n'.join(instructions).replace(instr+'\n', new_instr+'\n').split('\n')
            #bp()
            complete, accumulator = run_program(replaced)
            if complete:
                break
    print('Part 2:', accumulator)

if __name__ == "__main__":
    main()
