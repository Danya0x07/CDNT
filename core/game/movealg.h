#ifndef _CORE_GAME_MOVEALG_H
#define _CORE_GAME_MOVEALG_H

#include "entities.h"

void movealg_classic(entity_id entity);
void movealg_simplified(entity_id entity);
void movealg_quick(entity_id entity, uint32_t *timeout);
void movealg_pltlamp(entity_id entity);
void movealg_pltcam(entity_id entity);

#endif // _CORE_GAME_MOVEALG_H