using DelimitedFiles

function breed(school)
    num_new_fish = count(fish -> (fish == 0), school)
    school = [fish == 0 ? 6 : (fish - 1) for fish in school]

    school = hcat(school, 8 * ones(Int, 1, num_new_fish))
    return school
end

function main()
    school = readdlm("inputs/6.txt", ',', Int)

    days = 80
    for day = 1:days
        school = breed(school)
    end
    println("First part: ", length(school))
end
main()
