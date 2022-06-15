/* Firmware configuration file. */

#ifndef _CORE_CONFIG_H
#define _CORE_CONFIG_H

#include <info.h>

#define LANGUAGE    LANG_EN

// Spirits parameters.
#define ACTION_TIMEOUT_YELLOW   5500
#define ACTION_TIMEOUT_BLUE     6000
#define ACTION_TIMEOUT_RED      5000
#define ACTION_TIMEOUT_PLTLAMP  9000
#define ACTION_TIMEOUT_PLTCAM   8000

#define NUM_OF_QUICK_MOVE_PREPARE_DEGREES   4
#define ACTION_TIMEOUT_QUICK    500
#define QUICK_LAST_MOVE_TIMEOUT_MULTIPLIER  2

// FLASH lights parameters
#define FLASH_LIGHTING_DURATION 300
#define FLASH_RECHARGE_TIMEOUT  7000

#define PWR_COST_IDLE   1
#define PWR_COST_LAMP   2
#define PWR_COST_TV     2
#define PWR_COST_CEILING    3
#define PWR_COST_FLASH  3
#define PWR_KILL_DELAY  2000
#define PWR_OFF_TIME    10000

#define CLOCK_TICK_PERIOD   90000

#endif // _CORE_CONFIG_H