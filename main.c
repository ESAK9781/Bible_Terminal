#include <ncurses.h>
#include <stdlib.h>
#include "./lib/renderUtil.h"







int main(int nArgs, char ** args) {
    initscr();

    addstr("----------------\nBible Terminal App\nC4C Sakamoto\n----------------\n");
    refresh();





    drawBox(0, 0, getmaxx(stdscr) - 1, getmaxy(stdscr) - 1, '$');

    getch();

    endwin();
}