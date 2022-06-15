#ifndef _CORE_GAME_COMPONENTS_H
#define _CORE_GAME_COMPONENTS_H

#include <house.h>

#include "entities.h"
#include "slots.h"
#include "routes.h"

typedef enum __attribute__((packed)) {
    COMPONENT_ACTIVITY,
    COMPONENT_VIEW,
    COMPONENT_SLOT,
    COMPONENT_ROUTE,
    COMPONENT_READINESS,
    NUM_OF_COMPONENTS
} component_id;

struct cpn_activity {
    uint8_t lvl;
};

struct cpn_view {
    enum __attribute__((packed)) {
        VISIBILITY_NONE,
        VISIBILITY_W,
        VISIBILITY_UV
    } visibility;
    enum drawing_color color;
};

struct cpn_slot {
    enum slot_type type;
    uint8_t idx;
};

struct cpn_route {
    enum route_variant variant;
};

struct cpn_readiness {
    uint8_t degree;
};

void *component_get(entity_id entity, component_id component);

#endif // _CORE_GAME_COMPONENTS_H