#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include "ui.h"
#include "rvcon-log.h"

static void ui_cleanup();
static void ui_handle_signal(int sig);
static ui_config_t *ui_config;

int ui_init(ui_config_t *config) {
	ui_config = config;
	/* Curses Initialization */
	signal(SIGINT, ui_handle_signal); /* arrange interrupts to terminate */
	initscr(); /* initialize the curses library */
	keypad(stdscr, TRUE); /* enable keyboard mapping */
	nonl(); /* tell curses not to do NL->CR/NL on output */
	cbreak(); /* take input chars one at a time, no wait for \n */
	noecho();
	return 0;
}

int ui_send_event(ui_event_type_t type) {
	ui_event_t event;
	event.type = type;
	if (ui_config->event_cb)
		return (ui_config->event_cb(&event));
	return 0;
}

/* UI Loop */
void ui_start() {
	int c;
	while (1) {
		c = getch(); /* refresh, accept single keystroke of input */
		mvprintw(0, 0, "c=%03d", c, c);
		refresh();
		switch (c) {
		case 'q':
			ui_cleanup();
			break;
		case KEY_UP:
			ui_send_event(UI_EVENT_FWD);
			break;
		case KEY_DOWN:
			ui_send_event(UI_EVENT_BACK);
			break;
		case KEY_LEFT:
			ui_send_event(UI_EVENT_LEFT);
			break;
		case KEY_RIGHT:
			ui_send_event(UI_EVENT_RIGHT);
			break;

		}
	}
}

/* Clean-up function */
static void ui_cleanup() {
	endwin();
	if (ui_config->exit_cb) {
		ui_config->exit_cb();
	}
}

static void ui_handle_signal(int sig) {
	ui_cleanup();
}
