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
    freeBible(bible);
    printf("Testing complete!\n");
}