#include "../vectors/vectors.h"
#include "../searchUtil/searchUtil.h"
#include "bible.h"
#include <string.h>

#define BOOK_SPLIT '!'
#define CHAPTER_SPLIT '#'
#define VERSE_SPLIT ':'

/**
 * @brief create a bible struct
 * @param txtPath path to the bible file
 * @return pointer to the new struct
 */
Bible * createBible(char * txtPath) {
    Bible * bible = malloc(sizeof(Bible));
    bible->books = _createList();
    FILE * file = fopen(txtPath, "r");

    char line[600];

    Book * currentBook;
    Chapter * currentChapter;
    int chapterNumber;
    int verseNumber;

    while (fgets(line, 600, file) != NULL) {
        if (strlen(line) == 0) continue; // just in case a blank line snuck in there somewhere 

        if (line[0] == BOOK_SPLIT) {
            // book
            currentBook = createBook();
            chapterNumber = 0;
            verseNumber = 0;

            // set the new book's name
            int bookNameSize = strlen(line) - 1; // -2 for newline and identifier, +1 for null char
            char * bookName = calloc(bookNameSize, sizeof(char));
            strncpy(bookName, &line[1], bookNameSize - 1);
            line[bookNameSize - 1] = '\0';
            currentBook->name = bookName;

            _append(bible->books, currentBook);
        } else if (line[0] == CHAPTER_SPLIT) {
            // chapter
            currentChapter = createChapter();
            currentChapter->number = chapterNumber;
            chapterNumber++;

            verseNumber = 0;
            
            _append(currentBook->chapters, currentChapter);
        } else if (line[0] == VERSE_SPLIT) {
            // verse
            Verse * nextVerse = createVerse();
            nextVerse->ref = createReference(_getLen(bible->books) - 1, 
                chapterNumber - 1, verseNumber);
            verseNumber++;

            int verseLength = strlen(line) - 1; // -2 for newline and identifier, +1 for null char
            nextVerse->text = calloc(verseLength, sizeof(char));
            strncpy(nextVerse->text, &line[1], verseLength - 1);
            nextVerse->text[verseLength - 1] = '\0';

            _append(currentChapter->verses, nextVerse);
        } else {
            printf("ERROR: Unable to read line: %s\n", line);
        }
    }

    return bible;
}

/**
 * @brief create an empty book struct
 * @return pointer to the new struct
 */
Book * createBook() {
    Book * out = malloc(sizeof(Book));
    out->chapters = _createList();
    out->name = NULL;
    return out;
}

/**
 * @brief create an empty chapter struct
 * @return pointer to the new struct
 */
Chapter * createChapter() {
    Chapter * out = malloc(sizeof(Chapter));
    out->number = 0;
    out->verses = _createList();
    return out;
}

/**
 * @brief create an empty verse struct
 * @return pointer to the new struct
 */
Verse * createVerse() {
    Verse * out = malloc(sizeof(Verse));
    out->text = NULL;
    return out;
}

/**
 * @brief create an empty reference struct
 * @param book the number of the book its in
 * @param chapter the number of the chapter its in
 * @param verseNum the number of this verse
 * @return the new reference
 */
Reference createReference(int bookNum, int chapterNum, int verseNum) {
    Reference out;
    out.book = bookNum;
    out.chapter = chapterNum;
    out.verse = verseNum;
    return out;
}

/**
 * @brief clone a verse reference struct
 * @param ref previous reference
 * @return pointer to cloned reference
 */
Reference * cloneReference(Reference ref) {
    Reference * out = malloc(sizeof(Reference));
    *out = ref;
    return out;
}

/**
 * @brief free a bible struct
 * @param bible pointer to the bible struct
 */
void freeBible(Bible * bible) {
    while (bible->books->size) {
        Book * book = _pop(bible->books);
        freeBook(book);
    }

    free(bible);
}

/**
 * @brief free a book struct
 * @param book pointer to the book struct
 */
void freeBook(Book * book) {
    while (book->chapters->size) {
        Chapter * chapter = _pop(book->chapters);
        freeChapter(chapter);
    }

    free(book->name);
    free(book);
}

/**
 * @brief free a chapter struct
 * @param chapter pointer to the chapter struct
 */
void freeChapter(Chapter * chapter) {
    while (chapter->verses->size) {
        Verse * verse = _pop(chapter->verses);
        freeVerse(verse);
    }

    free(chapter);
}

/**
 * @brief free a verse struct
 * @param verse pointer to the verse struct
 */
void freeVerse(Verse * verse) {
    free(verse->text);
    free(verse);
}

/**
 * @brief free a reference struct
 * @param ref pointer to the reference struct
 */
void freeReference(Reference * ref) {
    free(ref);
}

/**
 * @brief get a specific book
 * @param bible pointer to the bible
 * @param bookName name of the book
 * @return pointer to the appropriate book
 */
Book * getBook(Bible * bible, char * bookName) {
    for (int i = 0; i < _getLen(bible->books); i++) {
        Book * curBook = _getVal(bible->books, i);
        if (strcmp(bookName, curBook->name) == 0) {
            return curBook;
        }
    }

    printf("ERROR: Could not find book %s\n", bookName);
    return NULL;
}

/**
 * @brief get a specific chapter
 * @param book pointer to the book the chapter is in
 * @param index the index of the chapter (chapter # - 1)
 * @return pointer to the appropriate chapter
 */
Chapter * getChapter(Book * book, int index) {
    Chapter * out = _getVal(book->chapters, index);
    return out;
}

/**
 * @brief get a specific verse based on its reference
 * @param bible pointer to the bible
 * @param reference string with the verse's reference
 * @return pointer to the appropriate verse
 */
Verse * getVerse(Bible * bible, char * reference) {
    int colonPlace = -1;
    for (int i = 0; i < strlen(reference); i++) {
        if (reference[i] == ':') {
            colonPlace = i;
            break;
        }
    }
    
    if (colonPlace == -1) {
        printf("ERROR: Invalid search reference '%s'\n", reference);
        return NULL;
    }
    
    int verseNum = atoi(&reference[colonPlace + 1]);
    
    int spacePlace = -1;
    for (int i = 0; i < strlen(reference); i++) {
        if (reference[i] == ' ') {
            spacePlace = i;
        }
    }
    
    if (spacePlace == -1) {
        printf("ERROR: Invalid search reference '%s'\n", reference);
        return NULL;
    }
    
    char chapterString[10];
    for (int i = spacePlace + 1; i < colonPlace; i++) {
        chapterString[i - spacePlace - 1] = reference[i];
    }
    chapterString[colonPlace - spacePlace - 1] = '\0';
    int chapterNum = atoi(chapterString);
    
    char * bookName = calloc(spacePlace, sizeof(char));
    strncpy(bookName, reference, spacePlace);
    Book * book = getBook(bible, bookName);
    free(bookName);
    
    if (chapterNum > _getLen(book->chapters)) {
        printf("ERROR: Invalid search reference '%s'\n", reference);
        return NULL;
    }
    Chapter * chapter = _getVal(book->chapters, chapterNum - 1);

    if (verseNum > _getLen(chapter->verses)) {
        printf("ERROR: Invalid search reference '%s'\n", reference);
        return NULL;
    }
    Verse * verse = _getVal(chapter->verses, verseNum - 1);

    return verse;
}

/**
 * @brief get a specific verse based on its reference struct
 * @param bible pointer to the bible
 * @param ref pointer to the verse's reference struct
 * @return pointer to the appropriate verse
 */
Verse * rGetVerse(Bible * bible, Reference * ref) {
    Book * book = _getVal(bible->books, ref->book);
    Chapter * chapter = _getVal(book->chapters, ref->chapter);
    Verse * verse = _getVal(chapter->verses, ref->verse);
    return verse;
}

/**
 * @brief create a reference string based on the reference
 * @param bible pointer to the bible
 * @param ref pointer to the reference struct
 * @return string with the reference
 */
char * refString(Bible * bible, Reference * ref) {
    Book * book = _getVal(bible->books, ref->book);
    int stringLen = strlen(book->name) + 10;
    char * out = calloc(stringLen, sizeof(char));
    snprintf(&out[strlen(out)], stringLen, "%s %d:%d", book->name, ref->chapter + 1, ref->verse + 1);
    return out;
}

/**
 * @brief search all verses in the bible for a query string
 * @param bible pointer to the bible
 * @param query the string to search for
 * @return vector with all of the references of verses containing that query
 */
ListTemplate * searchVerses(Bible * bible, char * query) {
    ListTemplate * out = _createList();

    ListLink * bookLink = bible->books->head;
    while (bookLink != NULL) {

        ListLink * chapterLink = ((Book *) bookLink->value)->chapters->head;
        while (chapterLink != NULL) {

            ListLink * verseLink = ((Chapter *) chapterLink->value)->verses->head;

            while (verseLink != NULL) {
                if (searchString(((Verse *) verseLink->value)->text, query) != -1) {
                    _append(out, cloneReference(((Verse *) verseLink->value)->ref));
                }

                verseLink = verseLink->next;
            }

            chapterLink = chapterLink->next;
        }

        bookLink = bookLink->next;
    }

    return out;
}

