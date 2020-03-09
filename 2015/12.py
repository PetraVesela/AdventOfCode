import json
from itertools import chain

#uncomment l.7 for second part
def recursiveIterate(obj):
    if isinstance(obj, dict):
        #if not any(item == 'red' for item in obj.values()):
            for item in obj.values():
                yield from recursiveIterate(item)
    elif isinstance(obj, list):
        for item in obj:
            yield from recursiveIterate(item)
    else:
        yield obj

with open('inputs/12.txt') as content:
    jsonObjectList = json.loads(content.read())

totalSum = sum(x for x in recursiveIterate(jsonObjectList) if type(x) == int)
print(totalSum)
