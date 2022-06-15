#include <house.h>

#include "slots.h"
#include "components.h"

static entity_id drawing_slots[NUM_OF_DRAWINGS] = {NO_ENTITY};
static entity_id lamp_slots[NUM_OF_ROOM_LAMPS] = {NO_ENTITY};
static entity_id cam_slots[NUM_OF_CAMS] = {NO_ENTITY};
static entity_id tv_slot = NO_ENTITY;

static entity_id *const slots[4] = {drawing_slots, lamp_slots, cam_slots, &tv_slot};

void slot_occupy(entity_id entity, enum slot_type s_type, uint8_t s_idx)
{
    struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);
    struct cpn_slot bak_slot = *slot;

    slot_release(entity);

    /* Works properly if not trying to occupy busy slot 
     * having slot->type == SLOT_NONE.
     */
    entity_id occupier = slot_get_occupier(s_type, s_idx);
    if (occupier) {
        slot_release(occupier);
        slot_occupy(occupier, bak_slot.type, bak_slot.idx);
    }

    slot->type = s_type;
    slot->idx = s_idx;
    slots[s_type - 1][s_idx] = entity;
}

void slot_release(entity_id entity)
{
    struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);

    if (slot->type != SLOT_NONE)
        slots[slot->type - 1][slot->idx] = NO_ENTITY;
    slot->type = SLOT_NONE;
    slot->idx = 0;
}

entity_id slot_get_occupier(enum slot_type s_type, uint8_t s_idx)
{
    return slots[s_type - 1][s_idx];
}

bool slot_is_free(enum slot_type s_type, uint8_t s_idx)
{
    return slot_get_occupier(s_type, s_idx) == NO_ENTITY;
}

uint8_t slots_filter_free(enum slot_type s_type, uint8_t *s_idxs, uint8_t n_idxs)
{
    uint8_t nfree = 0;

    for (uint8_t i = 0; i < n_idxs; i++) {
        if (slot_is_free(s_type, s_idxs[i])) {
            s_idxs[nfree++] = s_idxs[i];
        }
    }
    return nfree;
}