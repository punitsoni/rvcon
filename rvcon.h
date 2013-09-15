#ifndef __MOCO_H__
#define __MOCO_H__

#define RV_MOTOR_CHANNELS  4

/* Rover Config */
typedef struct _rv_config_t {
   int pwm_gpio[RV_MOTOR_CHANNELS];
   int dir_gpio[RV_MOTOR_CHANNELS];
   int enc_gpio[RV_MOTOR_CHANNELS];
   int ch_front_left;
   int ch_front_right;
   int ch_back_left;
   int ch_back_right;
} rv_config_t;

extern rv_hw_config_t rv_config;

#endif
