#ifndef _CORE_GAME_MOVEALG_H
#define _CORE_GAME_MOVEALG_H

#include "entities.h"

#define PT_LAMP_TV  (1 << 0)
#define PT_CAM      (1 << 1)

void movealg_classic_move(entity_id entity);
void movealg_simplified_move(entity_id entity);
void movealg_quick_move(entity_id entity, uint32_t *act_timeout);
void movealg_static_move(entity_id entity, uint8_t possession_tgts);

void movealg_exorcise_from_lamp_to_drawing(entity_id entity);
void movealg_reset_route(entity_id entity);

#endif // _CORE_GAME_MOVEALG_H