# Uncomment lines 29 & 35 for the first part

function main()
    # Read input file
    f = open("inputs/5.txt", "r")

    filedump = read(f, String)
    lines = split(filedump, "\r\n")
    re = r"([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)"

    coords = zeros(Int, length(lines), 4)

    for row = 1:length(lines)
        for col = 1:4
            # 1-based indexing :(
            coords[row, col] = parse(Int, match(re, lines[row])[col]) + 1
        end
    end
    diagram_size = board_siez = (maximum(coords))

    diagram = zeros(Int, diagram_size, diagram_size)

    for coord in eachrow(coords)
        stride_row = coord[1] < coord[3] ? 1 : -1
        stride_col = coord[2] < coord[4] ? 1 : -1

        if coord[1] == coord[3] || coord[2] == coord[4]
            diagram[coord[2]:stride_col:coord[4], coord[1]:stride_row:coord[3]] .+= 1
            # #=
        else # diagonal strike
            indices = collect(zip(coord[2]:stride_col:coord[4], coord[1]:stride_row:coord[3]))
            indices = map(CartesianIndex, indices)
            diagram[indices] .+= 1
        end
        # =#
    end

    println("\nResult: ", count(x -> (x >= 2), diagram))
end

main()