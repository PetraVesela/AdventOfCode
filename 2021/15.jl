function find_min_cost_path(matrix)
    field_size = size(matrix)[1]
    # A helper matrix containing the value of cheapest path to the bottom right corner
    cost_matrix = -1 * ones(Int, size(matrix))

    end_cell = CartesianIndex(field_size, field_size)
    cost_matrix[end_cell] = 0

    # Initialize last row
    for c = (field_size-1):-1:1
        current = CartesianIndex(field_size, c)
        right = CartesianIndex(field_size, c + 1)
        cost_matrix[current] = matrix[right] + cost_matrix[right]
    end

    # Initialize last column
    for r = (field_size-1):-1:1
        ind = CartesianIndex(r, field_size)
        below = CartesianIndex(r + 1, field_size)
        cost_matrix[ind] = matrix[below] + cost_matrix[below]
    end

    # Initialize the rest
    for c = (field_size-1):-1:1
        for r = (field_size-1):-1:1
            current = CartesianIndex(r, c)
            right = CartesianIndex(r, c + 1)
            below = CartesianIndex(r + 1, c)
            if cost_matrix[right] + matrix[right] < cost_matrix[below] + matrix[below]
                cost_matrix[current] = matrix[right] + cost_matrix[right]
            else
                cost_matrix[current] = matrix[below] + cost_matrix[below]
            end
        end
    end

    return cost_matrix[CartesianIndex(1, 1)]
end

function main()
    # Read input file
    f = open("inputs/15.txt", "r")

    filedump = read(f, String)
    field_size = length(split(filedump, "\r\n"))
    m = transpose(reshape([parse(Int, digit) for num in split(filedump, "\r\n") for digit in num], field_size, field_size))

    println("First part: ", find_min_cost_path(m))
    bigger_matrix = [
        m m.+1 m.+2 m.+3 m.+4
        m.+1 m.+2 m.+3 m.+4 m.+5
        m.+2 m.+3 m.+4 m.+5 m.+6
        m.+3 m.+4 m.+5 m.+6 m.+7
        m.+4 m.+5 m.+6 m.+7 m.+8
    ]
    bigger_matrix[bigger_matrix.>9] .-= 9

    println("Second part: ", find_min_cost_path(bigger_matrix))

end

main()