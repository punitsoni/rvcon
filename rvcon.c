#include <stdio.h>
#include <unistd.h>
#include "rvcon.h"
#include "rv-config.h"
#include "ui.h"

#define USAGE_STR   \
    "usage: rvcon [options]\n" \
    "   -h : help\n"
#define TRUE    1
#define FALSE   0

typedef struct _rvcon_cmd_config_t {
    int curses_ui;
} rvcon_cmd_config_t;
static rvcon_cmd_config_t cmd_config;

static int parse_cmdline(int argc, char* argv[])
{
    int ch;
    while((ch = getopt(argc, argv, "hc")) != -1) {
        switch((char) ch) {
        case 'c':
            cmd_config.curses_ui = TRUE;
            break;
        case 'h':
        default:
            printf("%s", USAGE_STR);
        }
    }
    return 0;
}

void ui_exit_cb()
{
    printf("RVCON: bye bye...\n");
}

int main(int argc, char *argv[])
{
    printf("RVCON: Rover Controller\n");
    parse_cmdline(argc, argv);
    if(cmd_config.curses_ui == TRUE) {
        /* start curses based ui */
        ui_config_t ui_config;
        ui_config.exit_cb = ui_exit_cb;
        ui_init(&ui_config);
    }
    return 0;
}
