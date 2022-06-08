#ifndef _CORE_GAME_SCORE_H
#define _CORE_GAME_SCORE_H

#include <stdint.h>

void score_reset(void);
void score_add(uint8_t points);
uint16_t score_get(void);

#endif // _CORE_GAME_SCORE_H