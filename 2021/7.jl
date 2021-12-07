using DelimitedFiles

function arithm_sequence_sum(num)
   return div(num*(1 + num), 2)
end


function main()
    crabs = readdlm("inputs/7.txt", ',', Int)

    min_fuel = 1000000000 * ones(Int, 1,2)
    fuel = zeros(Int, 1,2)
    for crab in minimum(crabs) : maximum(crabs)
        fuel[1] = sum([abs(c-crab) for c in crabs])
        fuel[2] = sum([arithm_sequence_sum(abs(c-crab)) for c in crabs])
        if fuel[1] < min_fuel[1]
            min_fuel[1] = fuel[1]
        end
        if fuel[2] < min_fuel[2]
            min_fuel[2] = fuel[2]
        end
    end

    println("First part: ", min_fuel[1])
    println("Second part: ", min_fuel[2])
end


main()
