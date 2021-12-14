using Colors, Plots


function dict_to_matrix(dict, num_rows, num_columns)
    mat = zeros(Int, num_rows, num_columns)
    for k in CartesianIndices(mat)
        mat[k] = haskey(dict, k)
    end
    return mat
end


function matrix_to_dict(matrix)
    dict = Dict()
    for ind in CartesianIndices(matrix)
        if matrix[ind] == 1
            dict[ind] = matrix[ind]
        end
    end
    return dict
end


function main()
    # Read input file
    f = open("inputs/13.txt", "r")

    filedump = read(f, String)
    tasks = split(filedump, "\r\n\r\n")

    dots = Dict()
    for dot in split(tasks[1], "\r\n")
        nums = split(dot, ',')
        key = CartesianIndex((parse(Int, nums[2]) + 1, parse(Int, nums[1]) + 1))
        dots[key] = 1
    end

    # Find the field size
    num_rows = 0
    num_columns = 0
    for (k, v) in dots
        num_columns = (num_columns < k[2]) ? k[2] : num_columns
        num_rows = (num_rows < k[1]) ? k[1] : num_rows
    end

    # Build up the field
    matrix = dict_to_matrix(dots, num_rows + 2, num_columns)

    # Fold the field
    for (ind, line) in enumerate(split(tasks[2], "\r\n"))
        number = parse(Int, split(line, '=')[end])
        if line[12] == 'x'
            left = matrix[:, 1:number]
            flipped_right = reverse(matrix[:, number+2:end], dims = 2)
            matrix = left .| flipped_right
        elseif line[12] == 'y'
            upper = matrix[1:number, :]
            flipped_lower = reverse(matrix[number+2:end, :], dims = 1)
            matrix = upper .| flipped_lower
        end
        if ind == 1
            println("First part: ", sum(matrix))
        end
    end

    display(plot(Gray.(matrix)))
    readline()

end

main()