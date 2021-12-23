mutable struct SnailfishNumber
    left
    right
    function SnailfishNumber(str::String)
        lst = eval(Meta.parse(str))
        left = lst[1] isa Vector ? SnailfishNumber(lst[1]) : lst[1]
        right = lst[2] isa Vector ? SnailfishNumber(lst[2]) : lst[2]
        new(left, right)
    end

    function SnailfishNumber(vec::Vector)
        left = vec[1] isa Vector ? SnailfishNumber(vec[1]) : vec[1]
        right = vec[2] isa Vector ? SnailfishNumber(vec[2]) : vec[2]
        new(left, right)
    end
end

function Base.:+(x::SnailfishNumber, y::SnailfishNumber)
    return SnailfishNumber([x, y])
end

#######################################################################
#  Helper functions

function get_magnitude(n)
    mag = 0
    mag += (n.left isa Vector) ? 3 * get_magnitude(n.left) : 3 * n.left
    mag += (n.right isa Vector) ? 2 * get_magnitude(n.right) : 2 * n.right
    return mag
end

# SPLIT
function traverse_and_find_split(current_tree)
    if current_tree isa Integer
        if current_tree > 10
            error("Found a number that can be split")
        end
    else
        for node in [current_tree.left, current_tree.right]
            traverse_and_find_split(node)
        end
    end
end

function can_split(current_tree)
    try
        traverse_and_find_split(current_tree)
    catch e
        return true
    end
    return false
end


function find_split_and_split(current_tree, found_split)

    if current_tree isa Integer
        return false, current_tree
    end

    for (ind, node) in enumerate([current_tree.left, current_tree.right])
        if !(node isa SnailfishNumber) && node > 9
            if ind == 1
                current_tree.left = SnailfishNumber([Int(floor(node / 2)), Int(ceil(node / 2))])
            else
                current_tree.right = SnailfishNumber([Int(floor(node / 2)), Int(ceil(node / 2))])
            end
            return true, current_tree
        else
            found_split, node = find_split_and_split(node, found_split)
            if found_split
                return true, current_tree
            end
        end
    end
    return false, current_tree
end

# EXPLODE
function get_depth(number)
    return (number isa SnailfishNumber) ? 1 + maximum([get_depth(number.left), get_depth(number.right)]) : 0
end

function can_explode(number)
    return get_depth(number) > 4
end

function find_explosion_and_explode(current_tree, depth)
    println(depth)

    for node in [current_tree.left, current_tree.right]
        println(node)
        if node isa Integer # integers cannot explode
            continue
        end
        while (depth < 4 && depth != -1)
            carried, _, depth = find_explosion_and_explode(node, depth + 1)
        end
        if depth == 4
            carried = SnailfishNumber([node.left, node.right])
        end
        if depth != -1 || carried.left + carried.right != 0
            if carried.left + carried.right != 0
                if current_tree.left isa SnailfishNumber && depth == 4
                    current_tree.left = 0
                elseif carried.left != 0 && current_tree.left isa Integer
                    current_tree.left += carried.left
                    carried.left = 0
                end
                if current_tree.right isa SnailfishNumber && depth == 4
                    current_tree.right = 0
                elseif carried.right != 0 && current_tree.right isa Integer
                    current_tree.right += carried.right
                    carried.right = 0
                end
                return carried, current_tree, -1
            end
        end
    end
    return SnailfishNumber([0, 0]), current_tree, -1
end


#######################################################################

function main()

    f = open("inputs/18.txt", "r")
    lines = split(read(f, String), "\r\n")
    for ind = 1:length(lines)
        first = SnailfishNumber(String(lines[ind]))

        println(first)
        while (can_explode(first) || can_split(first))
            while can_explode(first)
                _, first = find_explosion_and_explode(first, 1)
                println(first)
            end
            #=while can_split(first)
                _, first = find_split_and_split(first, 1)
                println(first)
            end=#
        end

    end
end

main()