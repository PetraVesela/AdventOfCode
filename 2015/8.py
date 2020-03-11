def decode(string):
    return str(bytes(string, "utf-8").decode("unicode_escape"))[1:-1] #extra double quotes

def encodedLength(string):
    result = 0
    for c in string: # count occurrences of double quotes:
        if c == '"'  or c == '\\':
            result += 1
    return result + len(string) + 2

lines = []

with open('inputs/8.txt','r') as file:
    for line in file:
        lines.append(line)
        
numOfChars = sum( map( len, lines))
numOfActualChars = sum( map( len, map( decode, lines)))

print(numOfChars - numOfActualChars)

numOfEncodedChars = sum( map( encodedLength, lines))

print(numOfEncodedChars - numOfChars)
    
