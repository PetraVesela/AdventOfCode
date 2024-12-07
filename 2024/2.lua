function isAscending (lst)
	for ind = 1, #lst-1 do
		if lst[ind] >= lst[ind+1] then return false end
	end
	return true
end

function isDescending (lst)
	for ind = 1, #lst-1 do
		if lst[ind] <= lst[ind+1] then return false end
	end
	return true
end

function hasCorrectDifferences (lst)
	for ind = 1, #lst-1 do
		local diff = math.abs(lst[ind+1] - lst[ind])
		if diff < 1 or diff > 3 then
			return false
		end
	end

	return true
end

function isSafe (lst)
	return (isAscending(lst) or isDescending(lst)) and hasCorrectDifferences(lst)
end

function isSafeAfterRemoval (lst)
	for skipInd = 1, #lst do
		local newLst = {}
		for ind = 1, #lst do
			if ind ~= skipInd then
				table.insert(newLst, lst[ind])
			end
		end
		if isSafe(newLst) then
			return true
		end
	end
	return false
end


-- Read input file
local file = io.open("inputs/2.txt", "r");
local numSafe = 0
local numSafe_tol = 0
-- Parse the reports
for line in file:lines() do
	local report = {}
	for level in line:gmatch("%S+") do
		table.insert(report, tonumber(level))
	end
	if isSafe(report) then
		numSafe = numSafe+1
	elseif isSafeAfterRemoval(report) then
		numSafe_tol = numSafe_tol+1
	end
end

print("Number of safe reports:", numSafe)
-- Part 2

print("Number of reports within toleration:", numSafe_tol+numSafe)