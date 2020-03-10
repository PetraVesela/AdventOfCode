import operator as op

# because op.add_ didn't work
def bitwiseAdd(a,b):
    return a & b

dispatchBinaryOperator = {
    'OR': op.or_,
    'AND': bitwiseAdd,
    'LSHIFT': op.lshift,
    'RSHIFT': op.rshift
}


lines = []

with open('inputs/7.txt') as file:
    for line in file.readlines():
        lines.append((str(line).strip().split(' ')))

wires = {}
numWires = len(lines)

#init:
for line in lines[:]: # allows to mutate the iterable
    try:
        if len(line) == 3:
            value = int(line[0])
            wires[line[-1]] = value

    except:
        pass


while len(wires) < numWires:
    for line in lines[:]:
        
        if line[1] == '->' and line[0] in wires:
            wires[line[-1]] = wires[line[0]]
            
        elif line[0] == 'NOT' and line[1] in wires:
            wires[line[-1]] = 65535 - wires[line[1]]
            
        elif line[1] in dispatchBinaryOperator:
            
            try:
                a = int(line[0])
            except:
                if line[0] in wires:
                    a = wires[line[0]] 
                else:
                    a = 'notFound'
                
            try:
                b = int(line[2])
            except:
                if line[2] in wires:
                    b = wires[line[2]]
                else:
                    b = 'notFound'
            try:
                
                wires[line[-1]] = dispatchBinaryOperator[line[1]](a,b)
                
            except:
                pass
print(wires['a']) # for part 2, change the input file manually
