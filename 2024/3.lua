function getProduct (multiplication)
	local num_a, num_b = multiplication:match("mul%((%d*),(%d*)%)")
	return tonumber(num_a) * tonumber(num_b)
end

function getSearchStr(enabled)
	if enabled then return "don't%(%)" else return "do%(%)" end
end
	
-- Read input file
local file = io.open("inputs/3.txt", "r");

local result, result_2 = 0, 0
local multiplications = {}
local enabled = true
-- All of the input is a single memory, not the individual lines
for line in file:lines() do
	-- Prepare a vector with info on whether the index is enabled or disabled
	startPos, endPos = 0,0
	
	isEnabled = {}

	searchStr = getSearchStr(enabled)
	local counter = 1
	while true do
		startPos, endPos = line:find(searchStr, startPos+1)
		if not startPos then break end
		-- Store the values
		for ind = counter, endPos do
			isEnabled[ind] = enabled
		end
		-- Toggle to look for the other type of function
		counter = endPos+1
		enabled = not enabled
		searchStr = getSearchStr(enabled)
	end
	-- Add the enabled values until the end of the line
	for ind = counter, string.len(line) do
		isEnabled[ind] = enabled
	end

	-- Parse the multiplications	
	local startPos, endPos = 0,0
	while true do
		startPos, endPos = line:find("mul%(%d*,%d*%)", startPos+1)
		if not startPos then break end
		local multiplication = line:sub(startPos, endPos)
		-- Part 1
		local product = getProduct(multiplication)
		result = result + product
		-- Part 2
		if isEnabled[startPos] then
			result_2 = result_2 + product
		end
	end
end


print ("Part 1:", result)
print ("Part 2:", result_2)