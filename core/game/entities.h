#ifndef _CORE_GAME_ENTITIES_H
#define _CORE_GAME_ENTITIES_H

typedef enum __attribute__((packed)) {
    NO_ENTITY = 0,
    ENTITY_YELLOW,
    ENTITY_UV,
    ENTITY_RED,
    ENTITY_PLTLAMP,
    ENTITY_PLTCAM,
    NUM_OF_ENTITIES
} entity_id;

#endif