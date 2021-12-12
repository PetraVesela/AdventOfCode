FIELD_SIZE = 10

function dict_to_matrix(dict)
    mat = zeros(Int, FIELD_SIZE, FIELD_SIZE)
    for (k, v) in dict
        mat[k] = v
    end
    return mat
end


function matrix_to_dict(matrix)
    dict = Dict()
    for ind in CartesianIndices(matrix)
        dict[ind] = matrix[ind]
    end
    return dict
end

function get_neighbours(point, field_size)
    r = point[1]
    c = point[2]
    neighbours = [(r-1, c-1), (r-1, c), (r-1, c+1),
                  (r,   c-1),           (r,   c+1),
                  (r+1, c-1), (r+1, c), (r+1, c+1)
    ]

    out_of_range = Set([field_size + 1, 0])
    return [CartesianIndex(nb) for nb in neighbours if length(intersect(Set(nb), out_of_range)) == 0]
end

function get_number_of_flashing(octopuses, to_flash)
    # The octopus of 9 flash and energize neighbours
    num_flashed = 0
    for (ind, v) in to_flash
        # count itself
        num_flashed += 1
        octopuses[ind] = 10 # flashed, already counted

        # energize neighbours which haven't flashed
        nb = get_neighbours(ind, FIELD_SIZE)
        for n in nb
            octopuses[n] = octopuses[n] != 9 ? octopuses[n] + 1 : 0
        end
        # Did any neighbour flash?
        nb_to_flash = [n for n in nb if octopuses[n] == 0]

        for n in nb_to_flash
            octopuses[n] = 10
            octopuses, tmp = get_number_of_flashing(octopuses, Dict([(n, octopuses[n])]))
            num_flashed += tmp
        end
    end
    return octopuses, num_flashed
end


function main()
    # Read input file
    f = open("inputs/11.txt", "r")

    filedump = read(f, String)
    matrix = transpose(reshape([parse(Int, digit) for num in split(filedump, "\r\n") for digit in num], FIELD_SIZE, FIELD_SIZE))

    # translate to (x, y) -> val dictionary
    octopuses = matrix_to_dict(matrix)

    num_flashed = 0
    ind = 0
    while sum(dict_to_matrix(octopuses)) != 0
        # First, the energy level of each octopus increases by 1
        for (k, v) in octopuses
            octopuses[k] = v < 9 ? v + 1 : 0
        end
        to_flash = Dict([(k, v) for (k, v) in octopuses if v == 0])

        (octopuses, tmp) = get_number_of_flashing(octopuses, to_flash)
        num_flashed += tmp

        # Remove temporary markings
        for (k, v) in octopuses
            octopuses[k] = v > 9 ? 0 : v
        end
        ind += 1
        if ind == 100
            println("First part: ", num_flashed)
        end
    end
    println("Second part: ", ind)
end

main()