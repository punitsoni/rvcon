#ifndef __RVCON_H__
#define __RVCON_H__

#define RV_MOTOR_CHANNELS   4
#define CH_FRONT_LEFT       0
#define CH_FRONT_RIGHT      1
#define CH_BACK_LEFT        2
#define CH_BACK_RIGHT       3

/* Rover Config */
typedef struct _rv_config_t {
   int pwm_gpio[RV_MOTOR_CHANNELS];
   int dir_gpio[RV_MOTOR_CHANNELS];
   int enc_gpio[RV_MOTOR_CHANNELS];
   int cur_ana_in[RV_MOTOR_CHANNELS]; 
} rv_config_t;

extern const rv_config_t rv_config;

#endif
