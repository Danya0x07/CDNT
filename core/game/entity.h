#ifndef _CORE_GAME_ENTITY_H
#define _CORE_GAME_ENTITY_H

#include <stdint.h>
#include <stdbool.h>

#include <house.h>
#include "routes.h"
#include "slots.h"

typedef uint8_t entity_id_t;

#define NO_ENTITY    0

enum __attribute__((packed)) entity_visibility {
    VISIBILITY_NONE,
    VISIBILITY_W,
    VISIBILITY_UV
};

struct paranormal_entity {
    void *alg_data;
    entity_id_t id; // must start from 1
    enum drawing_color color;
    enum entity_visibility visibility;
    uint8_t activity_lvl;
    uint8_t possessivility_lvl;
    enum route route;
    enum slot_type slot_type;
    uint8_t slot_id;
};

#endif // _CORE_GAME_ENTITY_H