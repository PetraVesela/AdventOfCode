import re

REQUIRED = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid']

def byr_valid(val):
    return int(val) >= 1920 and int(val) <= 2002 and len(val) == 4

def iyr_valid(val):
    return int(val) >= 2010 and int(val) <= 2020 and len(val) == 4

def eyr_valid(val):
    return int(val) >= 2020 and int(val) <= 2030 and len(val) == 4

def hgt_valid(val):
    num = re.findall(r'\d+', val)

    if 'cm' in val:
        if int(*num) >= 150 and int(*num) <= 193:
            return True
    if 'in' in val:
        if int(*num) >= 59 and int(*num) <= 76:
            return True
    return False

def hcl_valid(val):
    if val[0] == '#' and len(val) == 7:
        try:
            int(val[1:], 16)
            return True
        except ValueError:
            pass
    return False

def ecl_valid(val):
    return val in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']

def pid_valid(val):
    try:
        int(val)
        return len(val) == 9
    except ValueError:
        return False
    return True

def cid_valid(val):
    return True

DISPATCHER = {
    'byr' : byr_valid,
    'iyr' : iyr_valid,
    'eyr' : eyr_valid,
    'hgt' : hgt_valid,
    'hcl' : hcl_valid,
    'ecl' : ecl_valid,
    'pid' : pid_valid,
    'cid' : cid_valid

}

def is_valid_passport_part_1(pp):
    for entry in REQUIRED:
        if entry not in pp.keys():
            return False
    return True


def is_valid_passport_part_2(pp):
    for entry in pp:

        if not DISPATCHER[entry](pp[entry]):
            return False
    return True



def main():
    with open("inputs/4.txt", 'r') as file:
        filedump = file.read()

    passports = filedump.split('\n\n')
    parsed_passports = []
    for pp in passports:
        passport = dict()
        entries = pp.split()
        for entry in entries:

            passport[entry.split(':')[0]] = entry.split(':')[1]
        parsed_passports.append(passport)

    valid_passports_part_1 = [pp for pp in parsed_passports if is_valid_passport_part_1(pp)]
    valid_passports_part_2 = [pp for pp in valid_passports_part_1 if is_valid_passport_part_2(pp)]

    print("Part 1: ", len(valid_passports_part_1))
    print("Part 2: ", len(valid_passports_part_2))

if __name__ == "__main__":
    main()
