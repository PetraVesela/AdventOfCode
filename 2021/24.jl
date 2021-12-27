# Apparently the condition on 11 is too strict to discard a solution.
# Solution to the second part was found by hand

# Input file is rewritten into the monad() function:
function monad(z, w, ind)
    a = [1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0]
    b = [12, 15, 11, -14, 12, -10, 11, 13, -7, 10, -2, -1, -4, -12]
    c = [4, 11, 7, 2, 11, 13, 9, 12, 6, 2, 11, 12, 3, 13]

    x = (z % 26) + b[ind]
    x = Int(x != w)

    if (a[ind] == 0 && x == 1)
        throw(DomainError(x))
    end
    if (a[ind] == 0)
        z = div(z, 26)
    end

    y = (x == 1) ? 26 : 1
    z *= y

    y = (x == 1) ? c[ind] + w : 0
    z += y

    return z
end

function fold_input(input)
    if length(input) == 0
        return 0
    else
        return foldr((input, msd) -> input + 10 * msd, reverse(input))
    end
end

function find_valid_number()
    input = [] # Stack of digits to test
    dead_end = Set() # List of paths that did not work

    while true
        z = 0
        for w = 9:-1:1
            if fold_input(input) in dead_end
                continue
            end
            push!(input, w) # Push a new digit onto the stack

            for ind = 1:14 # Validate digits left to right until the number either passes or x == 1 on steps down
                if ind > length(input)
                    push!(input, 9)
                end
                if fold_input(input) in dead_end
                    pop!(input)
                    continue
                end

                try
                    z = monad(z, input[ind], ind)
                catch e
                    dead = fold_input(input)
                    push!(dead_end, dead)

                    pop!(input)
                    z = 0
                    break

                end
                if z == 0 && ind == 14
                    println("FOUND ", fold_input(input))
                    sleep(0.1)
                end
            end
        end
        # nothing found, step back
        dead = fold_input(input)

        if !in(dead, dead_end)
            push!(dead_end, dead)
        end

        if input[end] > 1
            input[end] -= 1
        else
            pop!(input)
        end
    end
end

function main()
    x = find_valid_number()
end



main()