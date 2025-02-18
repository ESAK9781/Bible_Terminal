#include <ncurses.h>
#include <stdlib.h>
#include "./lib/bible/bible.h"






int main(int nArgs, char ** args) {
    printf("Running...\n");
    Bible * bible = createBible("./res/KJV_C.txt");
    printf("Bible loaded!\n");
    char testRef[] = "1 Peter 4:9";
    printf("%s -- %s\n", testRef, getVerse(bible, testRef)->text);
    printf("Reference: %s\n", refString(bible, &getVerse(bible, testRef)->ref));

    ListTemplate * verses = searchVerses(bible, "Holy Spirit");
    for (int i = 0; i < _getLen(verses); i++) {
        Reference * ref = _getVal(verses, i);
        printf("\t%s -- %s\n", refString(bible, ref), rGetVerse(bible, ref)->text);
    }
    _deleteList(verses);

    freeBible(bible);
    printf("Testing complete!\n");
}