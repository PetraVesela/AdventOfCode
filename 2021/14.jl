function add_to_dict(dict, key, rep)
    if haskey(dict, key)
        dict[key] += rep
    else
        dict[key] = rep
    end
    return dict
end


function diff_min_max(dict)

    all_letters = Set()
    for key in keys(dict)
        push!(all_letters, key[1], key[2])
    end
    counts = Set()
    for letter in all_letters
        repeats = 0
        for key in keys(dict)
            if letter in key
                cnt = count(x -> x == letter, key)
                repeats += cnt * dict[key]
            end
        end
        repeats = ceil(repeats / 2)
        push!(counts, Int(repeats))
    end
    return maximum(counts) - minimum(counts)
end

function main()
    # Read input file
    f = open("inputs/14.txt", "r")

    filedump = read(f, String)
    parts = split(filedump, "\r\n\r\n")

    # Split template into pairs
    polymer_template_pairs = [(parts[1][i:i+1]) for i = 1:length(parts[1])-1]

    # Compress into dict (pair => count of pair)
    polymer_template = Dict()
    for (pair) in polymer_template_pairs
        add_to_dict(polymer_template, pair, 1)
    end

    # Parse replacements
    replacements = Dict()
    for rep in split(parts[2], "\r\n")
        rule = split(rep, " -> ")
        replacements[rule[1]] = rule[2][1]
    end

    # Perform the replacements
    for step = 1:40
        orig_dict = copy(polymer_template)
        for pair in keys(orig_dict)
            new_pairs = [join([pair[1] replacements[pair]]), join([replacements[pair], pair[2]])]

            for np in new_pairs
                polymer_template = add_to_dict(polymer_template, np, orig_dict[pair])
            end
            polymer_template[pair] -= orig_dict[pair] # remove all the occurrences of original pair

        end
        # Remove keys that are not in the dict anymore
        polymer_template = Dict([(k, v) for (k, v) in polymer_template if v > 0])
        if step == 10
            println("First part: ", diff_min_max(polymer_template))
        end
    end
    println("Second part: ", diff_min_max(polymer_template))


end

main()