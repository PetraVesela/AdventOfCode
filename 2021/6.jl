using DelimitedFiles
function get_length(school)
    return sum([pair[2] for pair in school])
end


function breed(school)
    num_new_fish = get(Dict(school), 0, "NaN")

    # deduct the days
    for ind = 1:length(school)
        k, v = school[ind]
        new_key = (k == 0) ? 6 : (k - 1)
        school[ind] = (new_key, v)
    end

    # Add newborns
    if num_new_fish != "NaN"
        for ind = 1:length(school)
            if school[ind] == 8
                school[ind] = (8, num_new_fish + school[ind][2])
                break
            elseif ind == length(school)
                push!(school, (8, num_new_fish))
            end
        end
    end

    # compress the same tuples
    school_dict = Dict()
    for (key, val) in school
        if haskey(school_dict, key)
            school_dict[key] += val
        else
            school_dict[key] = val
        end
    end
    # convert back to array of tuples
    new_school = [(k, v) for (k, v) in school_dict]
    return new_school
end

function main()
    school = readdlm("inputs/6.txt", ',', Int)
    school = sort(school, dims = 1)

    # convert to tuples
    school = [(num, count(x -> x == num, school)) for num = 1:5]

    days = 256
    part_1_days = 80
    for day = 1:days
        school = breed(school)
        if day == part_1_days
            println("Part 1: ", get_length(school))
        end
    end
    println("Part 2: ", get_length(school))

end
main()
