import re

def is_valid_password_part_1(pw):
    num_repetitions = pw['password'].count(pw['letter'])
    return num_repetitions <= int(pw['end']) and num_repetitions >= int(pw['start'])


def is_valid_password_part_2(pw):
    start = int(pw['start']) - 1
    end = int(pw['end']) - 1

    return pw['password'][start] != pw['password'][end] and pw['letter'] in [pw['password'][start], pw['password'][end]]

def main():
    with open("inputs/2.txt", 'r') as file:
        filedump = file.read()

    lines = filedump.split('\n')

    parsed_passwords = [re.match(r'(?P<start>\d+)-(?P<end>\d+)\s(?P<letter>[a-z]):\s(?P<password>\w+)', password).groupdict() for password in lines]

    valid_passwords_part_1 = [pw for pw in parsed_passwords if is_valid_password_part_1(pw)]
    valid_passwords_part_2 = [pw for pw in parsed_passwords if is_valid_password_part_2(pw)]

    print("Part 1: ", len(valid_passwords_part_1))
    print("Part 2: ", len(valid_passwords_part_2))

if __name__ == "__main__":
    main()
