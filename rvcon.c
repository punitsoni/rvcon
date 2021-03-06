#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rvcon.h"
#include "rvcon-log.h"
#include "rv-hw-config.h"
#include "ui.h"
#include "controller.h"

#define USAGE_STR   \
    "usage: rvcon [options]\n"  \
    "   -c : curses based ui\n" \
    "   -h : help\n"

FILE* logfile = NULL;
char *logfile_name = "rvcon.log";

typedef struct _rvcon_cmd_config_t {
    int curses_ui;
} rvcon_cmd_config_t;
static rvcon_cmd_config_t cmd_config;

/* rover controller */
ctrl_t rctrl;

static int parse_cmdline(int argc, char* argv[])
{
    int ch;
    while((ch = getopt(argc, argv, "hc")) != -1) {
        switch((char) ch) {
        case 'c':
            cmd_config.curses_ui = true;
            break;
        case 'h':
        default:
            printf("%s", USAGE_STR);
            return -1;
        }
    }
    return 0;
}

void ui_exit_cb()
{
    ctrl_cleanup();
    P_INFO("RVCON: bye bye...\n");
    exit(0);
}

int ui_event_cb(ui_event_t *event)
{
    P_INFO("ui event received : %d\n", event->type);
    switch(event->type) {
    case UI_EVENT_FWD:
        ctrl_set_dir(rctrl, DIR_FWD);
        ctrl_set_speed(rctrl, 100);
        break;
    case UI_EVENT_BACK:
        ctrl_set_dir(rctrl, DIR_BACK);
        ctrl_set_speed(rctrl, 100);
        break;
    case UI_EVENT_LEFT:
        break;
    case UI_EVENT_RIGHT:
        break;
    default:
        P_ERR("invalid event type: %d\n", event->type);
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    logfile = stdout;
    if(parse_cmdline(argc, argv) < 0) {
        return -1;
    }
    if(cmd_config.curses_ui == true) {
        FILE *fp = fopen(logfile_name, "w");
        if(!fp) {
            P_ERR("cannot open file: %s", logfile_name);
            return -1;
        }
        logfile = fp;
        ctrl_create(rctrl, &rv_hw_config);
        /* init ui */
        ui_config_t ui_config;
        ui_config.exit_cb = ui_exit_cb;
        ui_config.event_cb = ui_event_cb;
        ui_init(&ui_config);
        ui_start();
    }
    P_INFO("RVCON: Rover Controller\n");
    return 0;
}
