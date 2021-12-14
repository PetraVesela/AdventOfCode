function main()
    # Read input file
    f = open("inputs/14.txt", "r")

    filedump = read(f, String)
    parts = split(filedump, "\r\n\r\n")

    polymer_template = collect(parts[1])

    replacements = Dict()
    for rep in split(parts[2], "\r\n")
        rule = split(rep, " -> ")
        replacements[rule[1]] = rule[2][1]
    end

    # Perform the replacements
    for step = 1:40
        to_insert = []
        for ind = 1:length(polymer_template)-1
            pair = join(polymer_template[ind:ind+1])
            push!(to_insert, replacements[pair])
        end
        last_element = polymer_template[end]
        polymer_template = collect(Iterators.flatten(zip(polymer_template, to_insert)))
        push!(polymer_template, last_element)
        if (step == 10)
            counts = [count(x -> x == letter, polymer_template) for letter in polymer_template]
            println("First part: ", maximum(counts) - minimum(counts))
        end
        println(step)

    end
    counts = [count(x -> x == letter, polymer_template) for letter in polymer_template]
    println("Second part: ", maximum(counts) - minimum(counts))


end

main()