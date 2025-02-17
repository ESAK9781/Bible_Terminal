#include <ncurses.h>
#include <stdlib.h>







int main(int nArgs, char ** args) {
    initscr();

    addstr("----------------\nBible Terminal App\nC4C Sakamoto\n----------------\n");
    refresh();

    getch();

    endwin();
}