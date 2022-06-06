#ifndef _CORE_GAME_MOVEALG_H
#define _CORE_GAME_MOVEALG_H

#include "entity.h"
#include "tmev.h"

struct alg_quick_arg {
    struct timeout_event *tmev;
    uint8_t stage;
};

void movealg_classic(void *arg);
void movealg_simplified(void *arg);
void movealg_quickly(void *arg);
void movealg_pltlamp(void *arg);
void movealg_pltcam(void *arg);

#endif // _CORE_GAME_MOVEALG_H