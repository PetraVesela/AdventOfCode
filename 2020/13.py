'''
Break from outer loop by using return and a function
Chinese remainder theorem
https://www.youtube.com/watch?v=zIFehsBHB8o
'''
from functools import reduce

def modular_inverse(n, mod):
    x = 1
    while (n % mod * x) % mod != 1:
        x += 1
    return x

def chinese_remainder(divisors, remainders):
    N_vec = []
    N = reduce(lambda x, y: x*y, divisors)
    for divisor in divisors:
        the_rest = [div for div in divisors if div != divisor]
        N_vec.append(reduce(lambda x, y: x*y, the_rest))

    modular_inverses = [modular_inverse(n, mod) for n, mod in zip(N_vec, divisors)]
    products = [x*y*z for x, y, z in zip(remainders, N_vec, modular_inverses)]
    return sum(products) % N



def part_1(timestamp, buses):
    ind = timestamp
    while True:
        for bus in  buses:
            if ind % bus == 0:
                result = (ind - timestamp)*bus
                print("Part 1: ", result)
                return
        ind += 1


def main():
    with open("inputs/13.txt", 'r') as f:
        filedump = f.read()

    timestamp, buses = filedump.split('\n')
    timestamp = int(timestamp)
    bus_numbers = [int(bus) for bus in buses.split(',') if bus != 'x']

    part_1(timestamp, bus_numbers)

    offsets = [buses.split(',').index(str(bus_number)) for bus_number in bus_numbers]
    remainders = [bus_number - offset if offset != 0 else 0 for bus_number, offset in zip(bus_numbers, offsets)]

    print('Part 2: ', chinese_remainder(bus_numbers, remainders))

if __name__ == "__main__":
    main()
