using DelimitedFiles

function get_rate(bits, type)
    sums = [sum(bits[:, ind]) for ind in 1:size(bits)[2]]
    if type == "gamma"
        return [(sum >= size(bits)[1]/2) ? 1 : 0 for sum in sums]
    elseif type == "epsilon"
        return [(sum < size(bits)[1]/2) ? 1 : 0 for sum in sums]
    end
end


function get_rating(bits, type)
    if type == "oxygen"
        flag = "gamma"
    elseif type == "co2"
        flag = "epsilon"
    end

    to_delete = []
    bit = 0
    while (size(bits)[1] != 1)
        bit += 1
        gr = get_rate(bits, flag)

        for row in 1:size(bits)[1]
            if bits[row, bit] != gr[bit]
                append!(to_delete, row)
            end
        end
        # Remove the rows
        bits = bits[setdiff(1:end, to_delete), :]
        to_delete = []
    end
    return parse( Int, join(bits); base=2)
end


function main()
    # Read the input into bool array
    numbers = readdlm("inputs/3.txt", '\n', String)[1:end]

    bits = reduce(vcat, permutedims.(collect.(numbers)))
    bits = [parse(Int, x) for x in bits]

    # Part 1: Sum the matrix column-wise
    gamma_rate = get_rate(bits, "gamma")
    epsilon_rate = get_rate(bits, "epsilon")

    gamma = parse(Int, join(gamma_rate); base=2)
    epsilon = parse(Int, join(epsilon_rate); base=2)

    println("Part 1: ", gamma*epsilon)

    # Part 2:

    println("Part 2: ", get_rating(bits, "oxygen") * get_rating(bits, "co2"))
end


main()