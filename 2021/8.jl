simple_digits = [2, 4, 3, 7]

digit_dict = Dict([
    (BitArray([1, 1, 1, 0, 1, 1, 1]), 0),
    (BitArray([0, 0, 1, 0, 0, 1, 0]), 1),
    (BitArray([1, 0, 1, 1, 1, 0, 1]), 2),
    (BitArray([1, 0, 1, 1, 0, 1, 1]), 3),
    (BitArray([0, 1, 1, 1, 0, 1, 0]), 4),
    (BitArray([1, 1, 0, 1, 0, 1, 1]), 5),
    (BitArray([1, 1, 0, 1, 1, 1, 1]), 6),
    (BitArray([1, 0, 1, 0, 0, 1, 0]), 7),
    (BitArray([1, 1, 1, 1, 1, 1, 1]), 8),
    (BitArray([1, 1, 1, 1, 0, 1, 1]), 9)
])


function decode(row)
    # Letter => segment mapping
    this_mapping = Dict()
    # decode index 1, 3, 6
    one = unique([Set(num) for num in collect(filter(digit -> length(digit) == 2, row))])
    seven = unique([Set(num) for num in collect(filter(digit -> length(digit) == 3, row))])

    this_mapping[only(setdiff(only(seven), only(one)))] = 1

    for seg in only(one)
        if count(segment -> (seg in segment), row[1:10]) == 9
            this_mapping[seg] = 6
        else
            this_mapping[seg] = 3
        end
    end

    # decode 2, 4
    four = unique([Set(num) for num in collect(filter(digit -> length(digit) == 4, row))])

    for seg in only(four)
        if count(segment -> (seg in segment), row[1:10]) == 7
            this_mapping[seg] = 4
        elseif count(segment -> (seg in segment), row[1:10]) == 6
            this_mapping[seg] = 2
        end
    end

    last_two = setdiff(
        Set(collect("abcdefg")),
        Set(keys(this_mapping))
    )

    for seg in last_two
        if count(segment -> (seg in segment), row[1:10]) == 4
            this_mapping[seg] = 5
        elseif count(segment -> (seg in segment), row[1:10]) == 7
            this_mapping[seg] = 7
        end
    end

    output = row[length(row)-3:end]
    decoded_digit = []
    # Translate:
    for digit in output
        bits = BitArray([0, 0, 0, 0, 0, 0, 0])
        for segment in digit
            bits[this_mapping[segment]] = 1
        end
        push!(decoded_digit, digit_dict[bits])
    end
    return parse(Int, join(decoded_digit))
end


function main()
    # Read input file
    f = open("inputs/8.txt", "r")

    filedump = read(f, String)
    displays = split(filedump, "\r\n")

    # Decode each display
    num_simple_digits = 0

    digit_sum = 0
    for display in displays
        digits = split(replace(display, " | " => " "), ' ')
        output = digits[length(digits)-3:end]
        num_simple_digits += sum([length(digit) in simple_digits ? 1 : 0 for digit in output])
        digit_sum += decode(digits)
    end
    println("Part 1: ", num_simple_digits)
    println("Part 2: ", digit_sum)
end

main()
