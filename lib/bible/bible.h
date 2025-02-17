#ifndef BIBLE_H
#define BIBLE_H

#include "../vectors/vectors.h"


typedef struct _bible_struct {
    ListTemplate * books;
} Bible;

typedef struct _reference_struct {
    Bible * bible;
    unsigned char book;
    unsigned char chapter;
    unsigned char verse;
} Reference;

typedef struct _verse_struct {
    Reference ref;
    char * text;
} Verse;

typedef struct _chapter_struct {
    ListTemplate * verses;
    int number;
} Chapter;

typedef struct _book_struct {
    ListTemplate * chapters;
    char * name;
} Book;



/**
 * @brief create a bible struct
 * @param txtPath path to the bible file
 * @return pointer to the new struct
 */
Bible * createBible(char * txtPath);

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

#endif