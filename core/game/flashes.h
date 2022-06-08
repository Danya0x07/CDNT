#ifndef _CORE_GAME_FLASHES_H
#define _CORE_GAME_FLASHES_H

#include <house.h>
#include "tmev.h"

void flashes_reset(void);
bool flash_shoot(enum flash flash, enum flash_mode mode);
enum flash_mode flash_get(enum flash flash);

extern struct timeout_event tmev_flash_off;
extern struct timeout_event tmev_lflash_recharge;
extern struct timeout_event tmev_rflash_recharge;

#endif // _CORE_GAME_FLASHES_H