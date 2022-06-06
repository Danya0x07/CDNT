/* Firmware configuration file. */

#ifndef _CORE_CONFIG_H
#define _CORE_CONFIG_H

#include <info.h>

#define LANGUAGE    LANG_RU

// Spirits parameters.
#define ACTION_TIMEOUT_YELLOW   5000
#define ACTION_TIMEOUT_BLUE     5000
#define ACTION_TIMEOUT_RED      5000
#define ACTION_TIMEOUT_PLTLAMP  10000
#define ACTION_TIMEOUT_PLTCAM   10000

#define MAX_ACTIVITY_LVL    20
#define MAX_POSSESSIVILITY_LVL  (MAX_ACTIVITY_LVL / 2)

#define NUM_OF_QUICK_MOVE_PREPARE_DEGREES   3
#define ACTION_TIMEOUT_QUICK    300

#endif // _CORE_CONFIG_H