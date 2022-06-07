#include "flashes.h"

#define FLASH_LIGHTING_DURATION 300
#define FLASH_RECHARGE_TIMEOUT  10000

static enum flash_mode modes[2] = {FLASH_MODE_OFF};
static bool ready[2] = {true, true};

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

static void flash_off_cb(void)
{
    modes[FLASH_L] = modes[FLASH_R] = FLASH_MODE_OFF;
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
