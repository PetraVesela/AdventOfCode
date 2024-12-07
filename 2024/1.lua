 -- Read input file
 local file = io.open("inputs/1.txt", "r");
 local left = {}
 local right = {}
 
 -- Construct two lists
 for line in file:lines() do
	local row = {}
	for w in line:gmatch("%S+") do
		table.insert(row, w)
	end
	table.insert (left, row[1]);
	table.insert (right, row[2]);		
 end
 
 -- Sort them and compare
 table.sort(left)
 table.sort(right)

local sum = 0
for ind, leftNum in ipairs(left) do
    sum = sum + math.abs(leftNum-right[ind])
end

print("Total distance between lists:", sum)

-- Part 2
local similarity_score = 0
for _, leftNum in ipairs(left) do
	local count = 0
	for _, rightNum in ipairs(right) do
		if leftNum == rightNum then
			count = count + 1
		end
	end
	similarity_score = similarity_score + count * leftNum
end

print("Similarity score:", similarity_score)