function add_to_dict(dict, segments)
    if haskey(dict, segments[1])
        push!(dict[segments[1]], segments[2])
    else
        dict[segments[1]] = [segments[2]]
    end
    return dict
end

function find_paths_to_end(path, connections, current, part)
    paths = Set()
    for next in current
        if (!haskey(connections, next) && next != "end") || # dead end
           next == "start"  # Don't return back to start
            continue
        end

        if part == 1
            if (islowercase(next[1]) && next in path)  # Small caves can only be visited once
                continue
            end
        else
            if islowercase(next[1]) && !can_be_entered(path, next) # Only 1 small cave can be re-entered
                continue
            end
        end
        push!(path, next)
        if next != "end"
            union!(paths, find_paths_to_end(path, connections, connections[next], part))
        else
            push!(paths, copy(path))
        end
        pop!(path)
    end
    return paths
end

function can_be_entered(path, this_cave)
    # if the cave was already visited:
    if this_cave in path
        small_caves = [cave for cave in path if (islowercase(cave[1]) && cave != "start")]
        counts_of_small_caves = [count(x -> (x == cave), path) for cave in small_caves]
        if in(2, counts_of_small_caves)
            return false
        end
    end
    return true
end


function main()
    # Read and parse input into a dictionary
    f = open("inputs/12.txt", "r")

    filedump = read(f, String)
    lines = split(filedump, "\r\n")

    connections = Dict()
    for line in lines
        segments = split(line, '-')
        connections = add_to_dict(connections, segments)
        connections = add_to_dict(connections, (segments[2], segments[1]))
    end

    # Find all paths
    paths = Set()
    start = connections["start"]
    path = ["start"]
    paths = find_paths_to_end(path, connections, start, 1)
    println("First part: ", length(paths))

    paths = Set()
    paths = find_paths_to_end(path, connections, start, 2)
    println("Second part: ", length(paths))

end

main()