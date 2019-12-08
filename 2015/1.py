# read the data
file  = open('inputs/1.txt', 'r')
data = file.read()

floor = 0
i = 0
# process
while floor != -1: #i < len(data): # here, choose which part you want to solve
    if data[i] == '(':
        floor += 1
    else:
        floor -= 1
    i+=1
print(floor)
print(i)
input("Press Enter to continue...")
