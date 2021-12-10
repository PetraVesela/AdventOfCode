corruption_mapping = Dict([
    (')', 3),
    (']', 57),
    ('}', 1197),
    ('>', 25137)
])


opening = collect("([{<")

bracket_pairs = Dict([
    ('(', ')'),
    ('[', ']'),
    ('{', '}'),
    ('<', '>')
])

function main()
    # Read input file
    f = open("inputs/10.txt", "r")

    lines = split(read(f, String), "\r\n")

    # Iterate over lines, ignore corrupted and evaluate the incomplete ones
    corruption_sum = 0
    completion_scores = []

    for (ind, line) in enumerate(lines)
        total_score = 0
        brackets = []
        corrupted = false
        for bracket in line
            if bracket in opening
                push!(brackets, bracket)
            elseif bracket == bracket_pairs[brackets[end]]
                pop!(brackets)
            else # Corrupted line
                corruption_sum += corruption_mapping[bracket]
                corrupted = true
                break
            end
        end
        # Evaluate missing
        if (!corrupted)
            while (length(brackets) != 0)
                bracket = pop!(brackets)
                total_score = (5 * total_score) + findfirst(x -> x == bracket, opening)
            end
            push!(completion_scores, total_score)
        end

    end

    completion_scores = sort(completion_scores)
    middle_completion_score = completion_scores[div(length(completion_scores), 2)+1]

    println("First part: ", corruption_sum)
    println("Second part: ", middle_completion_score)

end


main()
