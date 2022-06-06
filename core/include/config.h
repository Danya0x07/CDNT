/* Firmware configuration file. */

#ifndef _CORE_CONFIG_H
#define _CORE_CONFIG_H

#include <info.h>

#define LANGUAGE    LANG_RU

// Spirits parameters.
#define ACTION_PERIOD_YELLOW    5000
#define ACTION_PERIOD_BLUE      5000
#define ACTION_PERIOD_RED       5000
#define ACTION_PERIOD_PLT1  10000
#define ACTION_PERIOD_PLT2  10000

#define MAX_ACTIVITY_LVL    20
#define MAX_POSSESSIVILITY_LVL  (MAX_ACTIVITY_LVL / 2)

#define QUICK_MOVEALG_PREPARE_STAGES    3
#define QUICK_MOVEALG_ACTION_PERIOD     300

#endif // _CORE_CONFIG_H