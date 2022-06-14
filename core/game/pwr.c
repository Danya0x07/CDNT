#include "pwr.h"
#include "slots.h"
#include "ceilings.h"
#include "flashes.h"
#include "entities.h"
#include "camera.h"
#include <house.h>
#include <config.h>

static uint8_t consumption;
static enum pwr_status status = PWR_ON;

void pwr_init(void)
{
    consumption = PWR_COST_IDLE;
}

void pwr_update()
{
    uint8_t cs = PWR_COST_IDLE;

    for (enum room_lamp l = _RL_FIRST; l < NUM_OF_ROOM_LAMPS; l++) {
        if (!slot_is_free(SLOT_LAMP, l))
            cs += PWR_COST_LAMP;
    }

    if (!slot_is_free(SLOT_TV, 0))
        cs += PWR_COST_TV;

    for (enum ceiling c = _CEILING_FIRST; c < NUM_OF_CEILINGS; c++) {
        if (ceiling_get(c))
            cs += PWR_COST_CEILING;
    }

    if (flash_get(FLASH_L) != FLASH_MODE_OFF)
        cs += PWR_COST_FLASH;
    if (flash_get(FLASH_R) != FLASH_MODE_OFF)
        cs += PWR_COST_FLASH;
    
    if (cs != consumption) {
        consumption = cs;
    }
}

uint8_t pwr_consumption_get(void)
{
    return consumption;
}

bool pwr_consumption_exceeds(void)
{
    return consumption > PWR_CONSUMPTION_MAX && status == PWR_ON;
}

enum pwr_status pwr_status_get(void)
{
    return status;
}

static void kill_power(void)
{
    ceilings_off();
    flashes_reset();
    house_reset();
    entity_kick_away(slot_get_occupier(SLOT_TV, 0));
    for (enum room_lamp l = _RL_FIRST; l < NUM_OF_ROOM_LAMPS; l++)
        entity_kick_away(slot_get_occupier(SLOT_LAMP, l));
    
    status = PWR_OFF;
}

static void restore_power(void)
{
    camera_select(CAMP);
    status = PWR_ON;
}

struct timeout_event tmev_pwr_kill = {
    .timeout = PWR_KILL_DELAY,
    .callback = kill_power,
    .active = false,
    .periodic = false
};

struct timeout_event tmev_pwr_restore = {
    .timeout = PWR_OFF_TIME,
    .callback = restore_power,
    .active = false,
    .periodic = false
};