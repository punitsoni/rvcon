#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <stdint.h>

#define RV_MOTOR_CHANNELS   4

/* Rover Hardware Config */
typedef struct _rv_hw_config_t {
   int pwm_gpio[RV_MOTOR_CHANNELS];
   int dir_gpio[RV_MOTOR_CHANNELS];
   int enc_gpio[RV_MOTOR_CHANNELS];
   int cur_ana_in[RV_MOTOR_CHANNELS];
} rv_hw_config_t;

/* Opaque handle for controller object */
typedef struct _controller* ctrl_t;

typedef enum _ctrl_dir_t {
    DIR_FWD,
    DIR_BACK,
} ctrl_dir_t;

/* Public API */
int32_t ctrl_create(ctrl_t ctrl, const rv_hw_config_t *hw_config);
int32_t ctrl_destroy(ctrl_t ctrl);
int32_t ctrl_set_speed(ctrl_t ctrl, uint8_t  speed);
int32_t ctrl_set_dir(ctrl_t ctrl, ctrl_dir_t dir);

#endif
