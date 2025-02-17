# encodes a json bible into a format that the c program can understand

import json

with open("./txt/KJV_JSON.json", "r") as file:
    bible = json.loads(file.read())

newStr = ""

for book in bible.keys():
    newStr += f'!{book}\n'
    chapNum = 1
    for chapter in bible[book]:
        newStr += f'#Chapter {chapNum}\n'
        for verse in chapter:
            newStr += f':{verse}\n'
        chapNum += 1

with open("./txt/KJV_C.txt", "w") as file:
    file.write(newStr)