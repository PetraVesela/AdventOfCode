import re

NUM_BITS = 36

def main():
    with open("inputs/14.txt", 'r') as file:
        instructions = file.read().split('mask = ')

    memory_1 = dict()
    memory_2 = dict()

    for instr in instructions[1:]:
        mask, *assignments = instr.split('\n')
        for assignment in assignments:
            res = re.search(r'mem\[(\d+)\] = (\d+)', assignment)
            try:
                addr, value = list(map(int, res.groups()))
            except AttributeError:
                continue
            # PART 1:
            new_value = [None]*NUM_BITS
            for ind, bit in enumerate(format(value, '036b')):
                if mask[ind] == 'X':
                    new_value[ind] = bit
                else:
                    new_value[ind] = mask[ind]

            memory_1[addr] = int(''.join(new_value), 2)

            # PART 2:
            new_addresses = [list(format(addr, '036b'))]

            for ind in range(NUM_BITS):
                if mask[ind] == '1':
                    for addr in new_addresses:
                        addr[ind] = mask[ind]
                elif mask[ind] == 'X':
                    to_extend = []
                    for addr in new_addresses:
                        addr[ind] = '0'
                        tmp = addr.copy()
                        tmp[ind] = '1'
                        to_extend.append(tmp)
                    new_addresses.extend(to_extend)

            for addr in new_addresses:
                memory_2[int(''.join(addr), 2)] = value


    print('Part 1: ', sum(memory_1.values()))
    print('Part 2: ', sum(memory_2.values()))

if __name__ == "__main__":
    main()
