import re

def is_valid_password_part_1(pw):
    num_repetitions = pw[3].count(pw[2])
    return num_repetitions <= int(pw[1]) and num_repetitions >= int(pw[0])


def is_valid_password_part_2(pw):
    start = int(pw[0]) - 1
    end = int(pw[1]) - 1

    return pw[3][start] != pw[3][end] and pw[2] in [pw[3][start], pw[3][end]]

def main():
    with open("inputs/2.txt", 'r') as file:
        filedump = file.read()

    lines = filedump.split('\n')

    parsed_passwords = [re.match(r'(\d+)-(\d+)\s([a-z]):\s(\w+)', password).groups() for password in lines]

    valid_passwords_part_1 = [pw for pw in parsed_passwords if is_valid_password_part_1(pw)]
    valid_passwords_part_2 = [pw for pw in parsed_passwords if is_valid_password_part_2(pw)]

    print("Part 1: ", len(valid_passwords_part_1))
    print("Part 2: ", len(valid_passwords_part_2))

if __name__ == "__main__":
    main()
