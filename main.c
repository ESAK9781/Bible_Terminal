#include <ncurses.h>
#include <stdlib.h>
#include "./lib/bible/bible.h"






int main(int nArgs, char ** args) {
    printf("Running...\n");
    Bible * bible = createBible("./res/KJV_C.txt");
    printf("Bible loaded!\n");
    printf("Genesis 2:1 -- %s\n", getVerse(bible, "Genesis 2:1")->text);
    freeBible(bible);
    printf("Testing complete!\n");
}