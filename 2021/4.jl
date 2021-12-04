using DelimitedFiles

function is_bingo(boards)
    # If there is a bingo, return the winning board score
    bingo = -1 * ones(Int, size(boards[1], 1))
    for board in boards
        if any([bingo == board[i, :] for i = 1:size(board, 1)])
            return sum(board[board.!=-1])
        elseif any([bingo == board[:, i] for i = 1:size(board, 2)])
            return sum(board[board.!=-1])
        end
    end
    return 0
end


function remove_bingos(boards)
    to_delete = []
    bingo = -1 * ones(Int, size(boards[1], 1))
    for ind = 1:length(boards)
        board = boards[ind]
        if any([bingo == board[i, :] for i = 1:size(board, 1)])
            append!(to_delete, ind)
        elseif any([bingo == board[:, i] for i = 1:size(board, 2)])
            append!(to_delete, ind)
        end
    end

    boards = boards[setdiff(1:end, to_delete), :]
    return boards
end


function draw_number(num, boards)
    for board in boards
        board[board.==num] .= -1
    end
    return boards
end

function main()
    # Parse the input file
    filedump = readdlm("inputs/4.txt", '\n', String)[1:end]

    to_draw = [parse(Int, num) for num in split(filedump[1], ',')]

    board_size = length([parse(Int, num) for num in split(filedump[2])])

    boards = []
    ind = 2
    stride = board_size - 1
    while ind + stride <= length(filedump)
        rows = join(filedump[ind:ind+stride], " ")
        board = transpose(reshape([parse(Int, num) for num in split(rows)], board_size, board_size))
        push!(boards, board)
        ind += board_size
    end

    # Start playing
    # First round
    ind = 1
    winning_score = is_bingo(boards)
    while winning_score == 0
        boards = draw_number(to_draw[ind], boards)
        winning_score = is_bingo(boards)
        ind += 1
    end
    final_score = to_draw[ind-1]
    println("First part: ", final_score * winning_score)

    # Second round
    last_winning_score = is_bingo(boards)
    last_winning = 0

    for ind = 1:length(to_draw)
        boards = draw_number(to_draw[ind], boards)
        if size(boards)[1] != 0
            winning_score = is_bingo(boards)
        else
            break
        end
        boards = remove_bingos(boards)
        if winning_score != 0
            last_winning = to_draw[ind]
            last_winning_score = winning_score
        end
    end

    println("Second part: ", last_winning * last_winning_score)

end


main()