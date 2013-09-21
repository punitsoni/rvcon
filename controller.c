#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "pigpio.h"
#include "rvcon-log.h"
#include "controller.h"

#define MOTOR_DIR_FWD   0
#define MOTOR_DIR_BACK  1

#define GPIO_LOW        0
#define GPIO_HIGH       1

/* controller is singleton object, this refcount makes sure,
   that only one instance of it exists at anytime */
static int8_t ctrl_refcount=0;

static struct _controller {
   const rv_hw_config_t *hw_cfg;
} controller;


int32_t ctrl_create(ctrl_t ctrl, const rv_hw_config_t *hw_config)
{
    int i;
    if(ctrl_refcount != 0) {
        P_ERR("only one instance of controller can be created. refcount=%d",
            ctrl_refcount);
        return -EINVAL;
    }
    if(hw_config == NULL) {
        P_ERR("failed, hw_config=NULL");
        return -EINVAL;
    }
    ctrl = &controller;
    ctrl->hw_cfg = hw_config;
     
    if(gpioInitialise() < 0) {
        P_ERR("gpioInitialise() failed");
        return -EFAULT;
    }
    for(i=0; i<RV_MOTOR_CHANNELS; i++) {
        gpioSetMode(ctrl->hw_cfg->pwm_gpio[i], PI_OUTPUT);
        gpioSetPullUpDown(ctrl->hw_cfg->pwm_gpio[i], PI_PUD_DOWN);
        gpioWrite(ctrl->hw_cfg->pwm_gpio[i], GPIO_LOW);
        gpioSetMode(ctrl->hw_cfg->dir_gpio[i], PI_OUTPUT);
        gpioSetPullUpDown(ctrl->hw_cfg->dir_gpio[i], PI_PUD_DOWN);
        gpioWrite(ctrl->hw_cfg->dir_gpio[i], GPIO_LOW);
        gpioSetMode(ctrl->hw_cfg->enc_gpio[i], PI_INPUT);
        gpioSetPullUpDown(ctrl->hw_cfg->enc_gpio[i], PI_PUD_DOWN);
        gpioWrite(ctrl->hw_cfg->enc_gpio[i], GPIO_LOW);
    }
    ctrl_refcount = 1;
    return 0;
}

int32_t ctrl_destroy(ctrl_t ctrl)
{
    if(ctrl == NULL) {
        P_ERR("failed, ctrl=NULL");
        return -EINVAL;
    }
    gpioTerminate();
    memset(ctrl, 0x00, sizeof(struct _controller));
    ctrl_refcount = 0;
    ctrl = NULL;
    return 0;
}

/* current implementation only supports 0 or full speed */
int32_t ctrl_set_speed(ctrl_t ctrl, uint8_t speed)
{
    int i;
    if(!ctrl) {
        P_ERR("failed, ctrl=NULL");
        return -EINVAL;
    }
    for(i=0; i<RV_MOTOR_CHANNELS; i++) {
        gpioWrite(ctrl->hw_cfg->pwm_gpio[i], GPIO_HIGH);
    }
    return 0;
}

int32_t ctrl_set_dir(ctrl_t ctrl, ctrl_dir_t dir)
{
    int i;
    if(!ctrl) {
        P_ERR("failed, ctrl=NULL");
        return -EINVAL;
    }
    uint8_t gpio_val;
    if(dir == DIR_FWD) {
        gpio_val = GPIO_HIGH;
    } else if(dir == DIR_BACK) {
        gpio_val = GPIO_LOW;
    } else {
        P_ERR("failed, invalid arg, dir=%d", dir);
        return -EINVAL;
    }
    for(i=0; i<RV_MOTOR_CHANNELS; i++) {
        gpioWrite(ctrl->hw_cfg->dir_gpio[i], gpio_val);
    }
    return 0;
}
