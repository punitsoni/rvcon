#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include "ui.h"

static void finish(int sig);
static void (*ui_exit_cb)();

int ui_init(ui_config_t *config)
{
    /* Curses Initialization */
    int num;

    ui_exit_cb = config->exit_cb;

    signal(SIGINT, finish);     /* arrange interrupts to terminate */
    initscr();                  /* initialize the curses library */
    keypad(stdscr, TRUE);       /* enable keyboard mapping */
    nonl();      /* tell curses not to do NL->CR/NL on output */
    cbreak();    /* take input chars one at a time, no wait for \n */
    noecho();      /* echo input - in color */

#if 0
    if (has_colors())
    {
        start_color();

        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    }
#endif

    while(1)
    {
        int c = getch();     /* refresh, accept single keystroke of input */
        //attrset(COLOR_PAIR(num % 8));
        num++;
        /* process the command keystroke */
        mvprintw(5, 10, "char=%c, key_code = %03d", c, c);
        refresh();
        switch (c) {
        case 'q':
            finish(0);
        }
    }
    finish(0);
}

static void finish(int sig)
{
    endwin();
    if(ui_exit_cb) {
        ui_exit_cb();
    }
    exit(0);
}

