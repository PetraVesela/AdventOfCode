'''
Partial sums
'''
def main():
    with open("inputs/1.txt", 'r') as file:
        filedump = file.read()

    numbers = [int(num) for num in filedump.split('\n')]

    incs = 0
    for ind in range(1, len(numbers)):
        if numbers[ind] > numbers[ind-1]:
            incs += 1
    print("First part: ", incs)

    incs = 0
    for ind in range(3, len(numbers)):
        if numbers[ind] > numbers[ind-3]:
            incs += 1
    print("Second part: ", incs)


if __name__ == "__main__":
    main()