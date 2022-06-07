#ifndef _CORE_GAME_ENTITIES_H
#define _CORE_GAME_ENTITIES_H

#include <stdint.h>

typedef enum __attribute__((packed)) {
    NO_ENTITY = 0,
    ENTITY_YELLOW,
    ENTITY_UV,
    ENTITY_RED,
    ENTITY_PLTLAMP,
    ENTITY_PLTCAM,
    NUM_OF_ENTITIES = ENTITY_PLTCAM
} entity_id;

void entity_setup(entity_id entity, uint8_t activity_lvl);
void entity_move(entity_id entity, void *arg);
void entity_kick_away(entity_id entity);

#endif