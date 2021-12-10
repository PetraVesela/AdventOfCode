function get_neighbours(point, field_size)
    r = point[1]
    c = point[2]
    neighbours = [            (r - 1, c),
                  (r, c - 1),            (r, c + 1),
                              (r + 1, c)
    ]

    return [CartesianIndex(nb) for nb in neighbours if (!in(nb[1], [0, field_size[1] + 1]) && !in(nb[2], [0, field_size[2] + 1]))]

end


function is_low_point(point, heightmap)
    val = heightmap[point]
    neighbours_values = [heightmap[ind] for ind in get_neighbours(point, size(heightmap))]
    is_higher = [n_val > val ? 0 : 1 for n_val in neighbours_values]
    return sum(is_higher) == 0
end


function get_segment_size(segment_size, point, heightmap)
    neighbours = get_neighbours(point, size(heightmap))

    # mark the visited points
    heightmap[point] = 9

    for nb in neighbours
        if heightmap[nb] != 9
            segment_size += 1
            heightmap[nb] = 9
            segment_size = get_segment_size(segment_size, nb, heightmap)
        end
    end
    return segment_size
end


function main()
    # Read input file
    f = open("inputs/9.txt", "r")

    filedump = read(f, String)

    heightmap = [parse(Int, digit) for num in split(filedump, "\r\n") for digit in num]
    num_rows = length(split(filedump, "\r\n"))
    num_columns = div(length(heightmap), num_rows)

    heightmap = transpose(reshape(heightmap, (num_columns, num_rows)))

    risk_level = 0
    low_points = []
    for ind in eachindex(heightmap)
        if is_low_point(ind, heightmap)
            push!(low_points, ind)
            risk_level += heightmap[ind] + 1
        end
    end

    println("First part: ", risk_level)

    # Second part
    segment_sizes = []
    for pt in low_points
        push!(segment_sizes,(get_segment_size(1, pt, heightmap)))
    end

    sorted_sizes = sort(segment_sizes, rev=true)

    println("Second part: ", sorted_sizes[1]*sorted_sizes[2]*sorted_sizes[3])
end


main()