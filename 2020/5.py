def main():
    with open("inputs/5.txt", 'r') as file:
        filedump = file.read()

    binary = filedump.replace('F', '0').replace('B', '1').replace('L', '0').replace('R', '1')
    seats = binary.split('\n')

    seat_IDs = set()
    for seat in seats:
        row = int(seat[:7], 2)
        column = int(seat[-3:], 2)
        seat_IDs.add(8*row + column)

    print("Highest seat ID: ", max(seat_IDs))

    ordered_IDs = sorted(seat_IDs)
    for seat_ID in range(ordered_IDs[0], len(ordered_IDs)):
        if seat_ID not in ordered_IDs:
            print(seat_ID)


if __name__ == "__main__":
    main()
