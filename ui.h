#ifndef __UI_H__
#define __UI_H__

typedef struct _ui_config_t {
    void (*exit_cb)();
} ui_config_t;

int ui_init(ui_config_t *config);

#endif
