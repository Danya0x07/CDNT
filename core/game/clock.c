#include <config.h>
#include <avr/pgmspace.h>

#include "clock.h"
#include "entities.h"
#include "components.h"

static uint8_t hour;

static const PROGMEM uint8_t activity_increments[NUM_OF_HOURS - 1][NUM_OF_ENTITIES] = {
    {1, 2, 0, 1, 0},
    {2, 1, 2, 1, 0},
    {1, 1, 1, 0, 1},
    {0, 1, 2, 2, 2},
    {1, 1, 3, 3, 2},
};

void clock_reset(void)
{
    hour = 0;
}

uint8_t clock_get(void)
{
    return hour;
}

static void tick(void)
{
    hour++;
    if (hour > NUM_OF_HOURS - 1)
        return;
      
    uint8_t idx = hour - 1;
    struct cpn_activity *activity;
    for (entity_id e = _ENTITY_FIRST; e < NUM_OF_ENTITIES; e++) {
        activity = component_get(e, COMPONENT_ACTIVITY);
        if (activity->lvl != 0) {
            activity->lvl += pgm_read_byte(&activity_increments[idx][e - 1]);
            if (activity->lvl > MAX_ACTIVITY_LVL)
                activity->lvl = MAX_ACTIVITY_LVL;
        }
    }
}

struct timeout_event tmev_clock = {
    .timeout = CLOCK_TICK_PERIOD,
    .callback = tick,
    .active = false,
    .periodic = true
};