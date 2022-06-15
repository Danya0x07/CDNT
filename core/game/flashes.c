#include <config.h>

#include "flashes.h"
#include "entities.h"
#include "components.h"
#include "slots.h"
#include "score.h"

static enum flash_mode modes[2] = {FLASH_MODE_OFF};
static bool ready[2] = {true, true};

void flashes_reset(void)
{
    modes[FLASH_L] = modes[FLASH_R] = FLASH_MODE_OFF;
    ready[FLASH_L] = ready[FLASH_R] = true;
    tmev_flash_off.active = false;
    tmev_lflash_recharge.active = false;
    tmev_rflash_recharge.active = false;
}

bool flash_shoot(enum flash flash, enum flash_mode mode)
{
    if (modes[FLASH_L] == FLASH_MODE_OFF && modes[FLASH_R] == FLASH_MODE_OFF && ready[flash]) {
        ready[flash] = false;
        modes[flash] = mode;
        return true;
    }
    return false;
}

enum flash_mode flash_get(enum flash flash)
{
    return modes[flash];
}

static void kick_entity_if_present(entity_id entity, enum flash flash)
{
    struct cpn_view *view = component_get(entity, COMPONENT_VIEW);

    if (!view)
        return;

    if (
        (modes[flash] == FLASH_MODE_W && view->visibility == VISIBILITY_W) ||
        (modes[flash] == FLASH_MODE_UV && view->visibility == VISIBILITY_UV)
    ) {
        entity_kick_away(entity);
        score_add(1);
    }
}

static void flash_off_cb(void)
{
    kick_entity_if_present(slot_get_occupier(SLOT_DRAWING, DRAWING_RPL), FLASH_L);
    kick_entity_if_present(slot_get_occupier(SLOT_DRAWING, DRAWING_RPR), FLASH_R);
    modes[FLASH_L] = modes[FLASH_R] = FLASH_MODE_OFF;
}

enum flash get_flash_for_uv_entity(void)
{
    if (slot_get_occupier(SLOT_DRAWING, DRAWING_RPL) == ENTITY_UV)
        return FLASH_L;
    else
        return FLASH_R;
}

static void lflash_recharge_cb(void)
{
    ready[FLASH_L] = true;
}

static void rflash_recharge_cb(void)
{
    ready[FLASH_R] = true;
}

struct timeout_event tmev_flash_off = {
    .timeout = FLASH_LIGHTING_DURATION,
    .callback = flash_off_cb,
    .active = false,
    .periodic = false
};

struct timeout_event tmev_lflash_recharge = {
    .timeout = FLASH_RECHARGE_TIMEOUT,
    .callback = lflash_recharge_cb,
    .active = false,
    .periodic = false
};

struct timeout_event tmev_rflash_recharge = {
    .timeout = FLASH_RECHARGE_TIMEOUT,
    .callback = rflash_recharge_cb,
    .active = false,
    .periodic = false
};
