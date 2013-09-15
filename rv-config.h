#include "rvcon.h"

const rv_config_t rv_config = {
    /* pwm_gpio */
    {
        18, /* Ch 0 */
        21, /* ch 1 */
        22, /* Ch 2 */
        23, /* Ch 3 */
    },
    /* dir_gpio */
    {
        24,
        25,
        7,
        8,
    },
    /* enc_gpio */
    {
        9,
        10,
        14,
        15,
    },
    /* cur_ana_in */
    {
        0,
        0,
        0,
        0,
    },
};

