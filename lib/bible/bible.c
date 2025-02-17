#include "../vectors/vectors.h"
#include "bible.h"
#include <string.h>

/**
 * @brief create a bible struct
 * @param txtPath path to the bible file
 * @return pointer to the new struct
 */
Bible * createBible(char * txtPath) {
    Bible * bible = malloc(sizeof(Bible));
    bible->books = _createList();
    FILE * file = fopen(txtPath, 'r');

    char line[600];

    Book * currentBook;
    Chapter * currentChapter;
    Verse * currentVerse;
    int chapterNumber;
    int verseNumber;

    while (fgets(line, 600, file) != NULL) {
        if (line[0] == '!') {
            // book
            currentBook = createBook();
            chapterNumber = 1;
            verseNumber = 1;

            int bookNameSize = strlen(line) - 2;
            char * bookName = calloc(bookNameSize, sizeof(char));
            for (int i = 0; i < bookNameSize; i++) {
                bookName[i] = line[i + 1];
            }
            line[bookNameSize - 1] = '\0';

            currentBook->name = bookName;

            _append(bible->books, currentBook);
        } else if (line[0] == '#') {
            // chapter
            currentChapter = createChapter();
            currentChapter->number = chapterNumber;
            chapterNumber++;
            
        } else if (line[0] == ':') {
            // verse

        } else {
            printf("ERROR: Unable to read line: %s\n", line);
        }
    }
}

/**
 * @brief create an empty book struct
 * @return pointer to the new struct
 */
Book * createBook();

/**
 * @brief create an empty chapter struct
 * @return pointer to the new struct
 */
Chapter * createChapter();

/**
 * @brief create an empty verse struct
 * @return pointer to the new struct
 */
Verse * createVerse();

/**
 * @brief create an empty reference struct
 * @param book pointer to the book its in
 * @param chapter pointer to the chapter its in
 * @param verseNum the number of this verse
 * @return pointer to the new reference
 */
Reference * createReference(Book * book, Chapter * chapter, int verseNum);

/**
 * @brief free a bible struct
 * @param bible pointer to the bible struct
 */
void freeBible(Bible * bible);

/**
 * @brief free a book struct
 * @param book pointer to the book struct
 */
void freeBook(Book * book);

/**
 * @brief free a chapter struct
 * @param chapter pointer to the chapter struct
 */
void freeChapter(Chapter * chapter);

/**
 * @brief free a verse struct
 * @param verse pointer to the verse struct
 */
void freeVerse(Verse * verse);

/**
 * @brief free a reference struct
 * @param ref pointer to the reference struct
 */
void freeReference(Reference * ref);

/**
 * @brief get a specific book
 * @param bookName name of the book
 * @return pointer to the appropriate book
 */
Book * getBook(char * bookName);

/**
 * @brief get a specific chapter
 * @param book pointer to the book the chapter is in
 * @param index the index of the chapter (chapter # - 1)
 * @return pointer to the appropriate chapter
 */
Chapter * getChapter(Book * book, int index);

/**
 * @brief get a specific verse based on its reference
 * @param reference string with the verse's reference
 * @return pointer to the appropriate verse
 */
Verse * getVerse(char * reference);

/**
 * @brief create a reference string based on the reference
 * @param ref pointer to the reference struct
 * @return string with the reference
 */
char * refString(Reference * ref);

/**
 * @brief search all verses in the bible for a query string
 * @param query the string to search for
 * @return vector with all of the verses containing that query
 */
ListTemplate searchVerses(char * query);

