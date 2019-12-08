import itertools
# read the data
file  = open('inputs/1.txt', 'r')
result = 0
secondResult = False 
frequencies = set() 
instructions = [] # list

for line in file:

	result += int(line)
	instructions.append(line)
	if result not in frequencies:
		frequencies.add(result)
	else:
		print(f'Second result: {result}')

file.close()

print(f'First result: {result}')

if not secondResult:
	instr = itertools.cycle(instructions)
	
	while True:
		result += int(next(instr))
		if result not in frequencies:
			frequencies.add(result)
		else:
			print(f'Second result: {result}')
			break



input("Press Enter to continue...")
