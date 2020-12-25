'''
Refactor
'''
import re
from collections import OrderedDict

def cannot_be_field(fields, value):
    result = set()
    for field in fields.items():
        if value not in field[1][0] and value not in field[1][1]:
            result.add(field[0])
    return result


def main():
    # Parse all the input
    with open("inputs/16.txt", 'r') as file:
        filedump = file.read().split('\n\n')

    valid_ranges = re.findall(r'\d+-\d+', filedump[0])
    for ind, range_t in enumerate(valid_ranges[:]):
        start, end = list(map(int, range_t.split('-')))
        valid_ranges[ind] = range(start, end+1)

    fields = dict()
    for ind, field in enumerate(filedump[0].split('\n')):
        name = field.split(':')[0]
        fields[name] = valid_ranges[ind*2 : ind*2 + 2]

    valid_numbers = set()
    for range_t in valid_ranges:
        valid_numbers.update(range_t)

    my_ticket = list(map(int, filedump[1].split('\n')[1].split(',')))
    nearby_tickets = filedump[2].split('\n')[1:]
    error_rate = 0

    # Remove invalid tickets and parse:
    for ind, ticket in enumerate(nearby_tickets[:]):
        numbers = list(map(int, ticket.split(',')))
        invalid = sum([number for number in numbers if number not in valid_numbers])
        nearby_tickets.remove(ticket)
        if invalid:
            error_rate += invalid
        else:
            nearby_tickets.append(numbers)

    print("Part 1: ", error_rate)

    # Start with all possibilities for all fields:
    identified_fields = dict()
    for ind in range(len(my_ticket)):
        identified_fields[ind] = set(fields.keys())


    # remove options that are not possible
    for ticket in nearby_tickets:
        for j, value in enumerate(ticket):
            ruled_out = cannot_be_field(fields, value)
            identified_fields[j] -= ruled_out

    # sort by number of possibilities:
    identified_fields = OrderedDict(sorted(identified_fields.items(), key=lambda x: len(x[1])))

    # clear out the rest:
    values_to_remove = set()

    for field in identified_fields.values():
        if len(field) != 1:
            field -= values_to_remove
        values_to_remove.add(*field)

    departure_indexes = set()
    for field in identified_fields:
        field_name = identified_fields[field].pop()
        if 'departure' in field_name:
            departure_indexes.add(field)

    result = 1
    for ind in departure_indexes:
        result *= my_ticket[ind]

    print('Part 2: ', result)

if __name__ == "__main__":
    main()
