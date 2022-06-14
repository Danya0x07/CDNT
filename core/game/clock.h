#ifndef _CORE_GAME_CLOCK_H
#define _CORE_GAME_CLOCK_H

#include "tmev.h"

void clock_reset(void);
uint8_t clock_get(void);

extern struct timeout_event tmev_clock;

#endif // _CORE_GAME_CLOCK_H