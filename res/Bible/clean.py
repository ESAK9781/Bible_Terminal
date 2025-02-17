
import json




# load the bible
bible = ""
with open("./txt/KJV_Raw.txt", 'r') as file:
    bible = file.read()
bible = bible.replace("\u2019", "'").replace("\u2014", "")
    
# split lines
bible_lines = bible.split("\n")


# extract the book names
print("Extracting books...")

lastBook = ""
parsedBooks = []

for line in bible_lines:
    if "1:" not in line:
        continue
    
    curBook = line.split(" 1:")[0]
    
    
    if (curBook == lastBook):
        if (curBook in parsedBooks):
            continue
        else:
            parsedBooks.append(curBook.strip())
            print("\tFound book: " + curBook.strip())
    else:
        lastBook = curBook

print("Successfully found " + str(len(parsedBooks)) + " books")

bible = {}
for book in parsedBooks:
    for line in bible_lines:
        if (line.startswith(book)):
            if book not in bible.keys():
                bible[book] = []
            bible[book].append(line.replace(book, "", 1).strip())

for book in bible.keys():
    verses = bible[book]
    chapters = []
    currChapterNum = -1
    currChapter = []
    allChapters = []
    
    for verse in verses:
        chapNum = int(verse.split(":")[0])
        if (chapNum != currChapterNum):
            currChapterNum = chapNum
            if (len(currChapter) != 0):
                allChapters.append(currChapter)
            currChapter = []
        
        currChapter.append(verse.split("\t", 1)[1])
    
    bible[book] = allChapters


with open("./txt/KJV_JSON.json", 'w') as file:
    file.write(json.dumps(bible, indent=2))