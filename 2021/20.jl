# Querying defaultdict for missing key adds the (key, defaultvalue) entry

function get_segment(point)
    r = point[1]
    c = point[2]
    neighbours = [(r - 1, c - 1), (r - 1, c), (r - 1, c + 1),
        (r, c - 1), (r, c), (r, c + 1),
        (r + 1, c - 1), (r + 1, c), (r + 1, c + 1)
    ]

    return [CartesianIndex(nb) for nb in neighbours]
end


function matrix_to_dict(matrix)
    dict = Dict()
    for ind in CartesianIndices(matrix)
        if matrix[ind] == '#'
            dict[ind] = 1
        else
            dict[ind] = 0
        end
    end
    return dict
end


function enhance(image, kernel, flag)
    new_image = Dict()

    # Enhance each pixel of original image
    for k in keys(image)
        segment = get_segment(k)
        bits = [get(image, pix, flag) for pix in segment]
        ind = foldr((bits, msd) -> bits + 2 * msd, reverse(bits))
        new_image[k] = kernel[ind+1]
        # Enhance neighbours also
        for pixel in segment
            if !(haskey(image, pixel))
                bits = [get(image, pix, flag) for pix in get_segment(pixel)]
                ind = foldr((bits, msd) -> bits + 2 * msd, reverse(bits))
                new_image[pixel] = kernel[ind+1]
            end
        end
    end
    return new_image
end


function main()
    # Read input file
    f = open("inputs/20.txt", "r")
    filedump = read(f, String)

    rows = split(filedump, "\r\n")
    kernel = rows[1]
    kernel = [(bit == '#') ? 1 : 0 for bit in kernel]

    image = rows[3:end]

    field_size = (length(image[1]), length(image))
    image = permutedims(reshape([char for row in image for char in row], field_size), (2, 1))

    # Convert matrix to dict (x,y) => 1 or 0
    image_dict = matrix_to_dict(image)

    # Run the enhancement
    for ind = 1:50
        flag = (kernel[1] == 1) ? (ind + 1) % 2 : 0
        image_dict = enhance(image_dict, kernel, flag)
        if ind == 2
            println("First part: ", sum(values(image_dict)))
        end
    end

    println("Second part: ", sum(values(image_dict)))


end

main()