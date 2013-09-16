#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

typedef struct _ctrl_config_t {
    int x; //todo
} ctrl_config_t;

typedef enum _ctrl_cmd_type_t {
    CTRL_MOVE_FWD,
    CTRL_MOVE_BACK,
    CTRL_STOP,
} ctrl_cmd_type_t;

typedef struct _ctrl_cmd_t {
    ctrl_cmd_type_t type;
    void *arg;
} ctrl_cmd_t;

int ctrl_init();
int ctrl_cleanup();
int ctrl_process_cmd(ctrl_cmd_t *cmd);

#endif
