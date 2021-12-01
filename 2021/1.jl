using DelimitedFiles

numbers = readdlm("inputs/1.txt", '\n', Int)

incs = 0
for ind = 2:length(numbers)
    if numbers[ind] > numbers[ind-1]
        global incs += 1
    end
end
print("First part: ", incs)

incs = 0
for ind = 4:length(numbers)
    if numbers[ind] > numbers[ind-3]
        global incs += 1
    end
end
print("\nSecond part: ", incs)
