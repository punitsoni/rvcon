#ifndef __UI_H__
#define __UI_H__

typedef struct _ui_event_t ui_event_t;

typedef struct _ui_config_t {
    void (*exit_cb)();
    int (*event_cb)(ui_event_t *event);
} ui_config_t;

typedef enum _ui_event_type_t {
    UI_EVENT_FWD,
    UI_EVENT_BACK,
    UI_EVENT_LEFT,
    UI_EVENT_RIGHT,
} ui_event_type_t;

typedef struct _ui_event_t {
    ui_event_type_t type;
} ui_event_t;

int ui_init(ui_config_t *config);
void ui_start();

#endif
