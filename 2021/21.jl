# Wrap a number into range
# numberToBeWrapped = start + (numberToBeWrapped - start) % (limit - start)

mutable struct DeterministicDice
    value::Int
    function DeterministicDice()
        new(1)
    end
end

function roll(d::DeterministicDice)
    vals = [d.value, d.value + 1, d.value + 2]
    vals[vals.>100] .-= 100
    d.value = (d.value + 3 > 100) ? d.value + 3 - 100 : d.value + 3
    return sum(vals)
end

function main()
    f = open("inputs/21.txt", "r")
    lines = split(read(f, String), "\r\n")

    # Parse the input
    player_pos = [0, 0]
    for ind = 1:length(lines)
        player_pos[ind] = parse(Int, lines[ind][end])
    end

    # Play the first game
    player_score = [0, 0]
    dice = DeterministicDice()
    player_ind = 1
    run = 0
    while player_score[1] < 1000 && player_score[2] < 1000
        val = roll(dice)
        new_position = val + player_pos[player_ind]
        pos = 1 + (new_position - 1) % 10
        player_pos[player_ind] = (pos)
        player_score[player_ind] += player_pos[player_ind]
        player_ind = (player_ind == 1) ? 2 : 1
        run += 1
    end
    println("First part: ", minimum(player_score) * 3 * run)
end

main()