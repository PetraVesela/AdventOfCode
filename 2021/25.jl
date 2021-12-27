function move_east(herd)
    field_size = size(herd)
    cucumbers = findall(herd .== '>')
    new_herd = deepcopy(herd)
    for c in cucumbers
        new_destination = CartesianIndex(c[1], ((c[2]) % (field_size[2])) + 1)
        if herd[new_destination] == '.'
            new_herd[c] = '.'
            new_herd[new_destination] = '>'
        end
    end
    return new_herd
end

function move_south(herd)
    field_size = size(herd)
    cucumbers = findall(herd .== 'v')
    new_herd = deepcopy(herd)
    for c in cucumbers
        new_destination = CartesianIndex(((c[1]) % (field_size[1])) + 1, c[2])
        if herd[new_destination] == '.'
            new_herd[c] = '.'
            new_herd[new_destination] = 'v'
        end
    end
    return new_herd
end

function main()
    # Read input file
    f = open("inputs/25.txt", "r")

    filedump = read(f, String)
    rows = split(filedump, "\r\n")
    field_size = (length(rows[1]), length(rows))
    herd = permutedims(reshape([char for row in rows for char in row], field_size), (2, 1))

    round = 0
    while true
        round += 1
        new_herd = move_east(herd)
        new_herd = move_south(new_herd)

        if herd == new_herd
            println("First part: $round")
            break
        else
            herd = new_herd
        end

    end

end

main()