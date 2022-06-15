#include <avr/pgmspace.h>

#include "components.h"

static struct cpn_activity activities[5];
static struct cpn_view views[3] = {
    {.visibility = VISIBILITY_W, .color = DCOLOR_YELLOW},
    {.visibility = VISIBILITY_UV, .color = DCOLOR_BLUE},
    {.visibility = VISIBILITY_W, .color = DCOLOR_RED},
};
static struct cpn_slot slots[5];
static struct cpn_route routes[3];
static struct cpn_readiness readinesses[1];

static void *const cpns_blocks[NUM_OF_COMPONENTS] = {
    [COMPONENT_ACTIVITY] = activities,
    [COMPONENT_VIEW] = views,
    [COMPONENT_SLOT] = slots,
    [COMPONENT_ROUTE] = routes,
    [COMPONENT_READINESS] = readinesses,
};

static const PROGMEM uint8_t cpns_idxs[1 + NUM_OF_ENTITIES][NUM_OF_COMPONENTS] = {
    [NO_ENTITY] = {0},
    [ENTITY_YELLOW] = {
        [COMPONENT_ACTIVITY] = 1,
        [COMPONENT_VIEW] = 1,
        [COMPONENT_SLOT] = 1,
        [COMPONENT_ROUTE] = 1,
    },
    [ENTITY_UV] = {
        [COMPONENT_ACTIVITY] = 2,
        [COMPONENT_VIEW] = 2,
        [COMPONENT_SLOT] = 2,
        [COMPONENT_ROUTE] = 2,
    },
    [ENTITY_RED] = {
        [COMPONENT_ACTIVITY] = 3,
        [COMPONENT_VIEW] = 3,
        [COMPONENT_SLOT] = 3,
        [COMPONENT_ROUTE] = 3,
        [COMPONENT_READINESS] = 1,
    },
    [ENTITY_PLTLAMP] = {
        [COMPONENT_ACTIVITY] = 4,
        [COMPONENT_SLOT] = 4,
    },
    [ENTITY_PLTCAM] = {
        [COMPONENT_ACTIVITY] = 5,
        [COMPONENT_SLOT] = 5,
    },
};

static const PROGMEM uint8_t cpns_sizes[NUM_OF_COMPONENTS] = {
    [COMPONENT_ACTIVITY] = sizeof(struct cpn_activity),
    [COMPONENT_VIEW] = sizeof(struct cpn_view),
    [COMPONENT_SLOT] = sizeof(struct cpn_slot),
    [COMPONENT_ROUTE] = sizeof(struct cpn_route),
    [COMPONENT_READINESS] = sizeof(struct cpn_readiness),
};

void *component_get(entity_id entity, component_id component)
{
    uint8_t idx = pgm_read_byte(&cpns_idxs[entity][component]);
    if (!idx)
        return NULL;
    idx--;

    uint8_t *block_addr = cpns_blocks[component];
    uint8_t block_size = pgm_read_byte(&cpns_sizes[component]);

    return block_addr + idx * block_size;
}
