#include "clock.h"
#include "entities.h"
#include "components.h"
#include <config.h>
#include <avr/pgmspace.h>

static uint8_t hour;

static const PROGMEM uint8_t activity_increments[NUM_OF_HOURS - 1][NUM_OF_ENTITIES] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 5},
    {3, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
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
            activity->lvl += pgm_read_byte(&activity_increments[idx][e]);
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