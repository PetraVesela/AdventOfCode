f = open("inputs/2.txt", "r")

lines = read(f, String)
lines = split(lines, "\r\n")

# First part
depth = 0
horizont = 0

for line in lines
    value = parse(Int, line[end])
    if line[1] == 'f'
        global horizont += value
    elseif line[1] == 'd'
        global depth += value
    elseif line[1] == 'u'
        global depth -= value
    end
end

println("First part: ", horizont * depth)


# Second part
aim = 0
depth = 0
horizont = 0

for line in lines
    value = parse(Int, line[end])
    if line[1] == 'f'
        global horizont += value
        global depth += (aim * value)
    elseif line[1] == 'd'
        global aim += value
    elseif line[1] == 'u'
        global aim -= value
    end
end
println("Second part: ", horizont * depth)
