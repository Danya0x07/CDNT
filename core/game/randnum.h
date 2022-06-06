#ifndef _CORE_GAME_RANDNUM_H
#define _CORE_GAME_RANDNUM_H

#include <stdint.h>

uint8_t randidx(uint8_t n);  // 0..n-1
uint8_t randnum(uint8_t max); // 1..max

#endif // _CORE_GAME_RANDNUM_H