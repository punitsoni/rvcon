#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "rvcon.h"
#include "pigpio.h"
#include "rvcon-log.h"
#include "controller.h"

#define MOTOR_DIR_FWD   0
#define MOTOR_DIR_BACK  1

#define GPIO_LOW        0
#define GPIO_HIGH       1


int ctrl_init()
{
    int i;
    if(gpioInitialise() < 0)
        return -1;
    for(i=0; i<RV_MOTOR_CHANNELS; i++) {
        gpioSetMode(rv_config.pwm_gpio[i], PI_OUTPUT);
        gpioSetPullUpDown(rv_config.pwm_gpio[i], PI_PUD_DOWN);
        gpioWrite(rv_config.pwm_gpio[i], GPIO_LOW);
        gpioSetMode(rv_config.dir_gpio[i], PI_OUTPUT);
        gpioSetPullUpDown(rv_config.dir_gpio[i], PI_PUD_DOWN);
        gpioWrite(rv_config.dir_gpio[i], GPIO_LOW);
        gpioSetMode(rv_config.enc_gpio[i], PI_INPUT);
        gpioSetPullUpDown(rv_config.enc_gpio[i], PI_PUD_DOWN);
        gpioWrite(rv_config.enc_gpio[i], GPIO_LOW);
    }
    return 0;
}

int ctrl_cleanup()
{
    gpioTerminate();
    return 0;
}

static int ctrl_set_motor_state(int id, int dir, int speed)
{
    /* speed control not supported for now */
    gpioWrite(rv_config.dir_gpio[id],dir);
    if(speed == 0)
        gpioWrite(rv_config.pwm_gpio[id], GPIO_LOW);
    else
        gpioWrite(rv_config.pwm_gpio[id], GPIO_HIGH);
    return 0;
}

static int ctrl_move_all(int dir, float speed)
{
    int i;
    for(i=0; i<RV_MOTOR_CHANNELS; i++) {
        ctrl_set_motor_state(i, dir, 1);
    }
    return 0;
}

static int ctrl_stop_all()
{
    int i;
    for(i=0; i<RV_MOTOR_CHANNELS; i++) {
        ctrl_set_motor_state(i, 0, 0);
    }
    return 0;
}

int ctrl_process_cmd(ctrl_cmd_t *cmd)
{
    if(!cmd) {
        P_ERR("failed");
        return -1;
    }
    switch(cmd->type) {
    case CTRL_MOVE_FWD:
       ctrl_move_all(MOTOR_DIR_FWD, 100.0f);
       break;
    case CTRL_MOVE_BACK:
       ctrl_move_all(MOTOR_DIR_BACK, 100.0f);
        break;
    case CTRL_STOP:
        ctrl_stop_all();
        break;
    default:
        P_ERR("invalid cmd type: %d", cmd->type);
        return -1;
    }
    return 0;
}
