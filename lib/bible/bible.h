#ifndef BIBLE_H
#define BIBLE_H

#include "../vectors/vectors.h"

struct _reference_struct;

typedef struct _verse_struct {
    _reference_struct ref;
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

typedef struct _bible_struct {
    ListTemplate * books;
} Bible;

typedef struct _reference_struct {
    Bible * bible;
    unsigned char book;
    unsigned char chapter;
    unsigned char verse;
} Reference;

Bible * createBible(char * txtPath);
Book * createBook();
Chapter * createChapter();
Verse * createVerse();
Reference * createReference(Book * book, Chapter * chapter, int verseNum);

void freeBible(Bible * bible);
void freeBook(Book * book);
void freeChapter(Chapter * chapter);
void freeVerse(Verse * verse);
void freeReference(Reference * ref);

Verse * getVerse()

#endif