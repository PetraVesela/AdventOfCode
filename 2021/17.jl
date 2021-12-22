function is_within_target(target, pt)
    return (pt[1] >= target[1] && pt[1] <= target[2]) &&
           (pt[2] >= target[3] && pt[2] <= target[4])
end


function is_beyond_target(target, pt)
    smaller_y = target[3] < target[4] ? target[3] : target[4]
    return (pt[1] > target[2] || pt[2] < smaller_y)
end


function main()
    # Parse the target coordinates
    f = open("inputs/17.txt", "r")
    filedump = read(f, String)

    re = r"([0-9]+)..([0-9]+), y=(-?[0-9]+)..(-?[0-9]+)"
    coords = match(re, filedump)
    target = zeros(Int, 4)
    for i = 1:4
        target[i] = parse(Int, coords[i])
    end

    # Shoot
    SEARCH_SPACE = 500 # Arbitrary but so what
    global_max_y = 0
    total_hits = 0
    for x = 1:SEARCH_SPACE
        for y = -SEARCH_SPACE:SEARCH_SPACE
            this_max_y = 0
            velocity = [x, y]
            pos = [0, 0]
            while (!is_within_target(target, pos) && !is_beyond_target(target, pos))
                pos .+= velocity
                if velocity[1] != 0
                    velocity[1] += (velocity[1] > 0) ? -1 : 1
                end
                velocity[2] -= 1
                this_max_y = (pos[2] > this_max_y) ? pos[2] : this_max_y
            end
            if is_within_target(target, pos)
                global_max_y = (global_max_y > this_max_y) ? global_max_y : this_max_y
                total_hits += 1
            end
        end
    end
    println("First part: $global_max_y")
    println("Second part: $total_hits")
end


main()
