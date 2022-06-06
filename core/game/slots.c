#include "entity.h"

extern struct paranormal_entity *get_entity_by_id(entity_id_t id);

static entity_id_t drawing_slots[NUM_OF_DRAWINGS] = {NO_ENTITY};
static entity_id_t __lamp_slots[NUM_OF_ROOM_LIGHTS] = {NO_ENTITY};
static entity_id_t __cam_slots[NUM_OF_CAMS - 1 /* RP cam can't be broken */] = {NO_ENTITY};
static entity_id_t __tv_slot = NO_ENTITY;

static entity_id_t *const slots[4] = {drawing_slots, __lamp_slots, __cam_slots, &__tv_slot};

void slot_occupy(struct paranormal_entity *e, enum slot_type s_type, uint8_t s_id)
{
    entity_id_t occupier_id = slot_get_occupier_id(s_type, s_id);
    enum slot_type e_slot_type = e->slot_type;
    uint8_t e_slot_id = e->slot_id;

    slot_release(e);

    /* Works properly if not trying to occupy busy slot 
     * having e->slot_type == SLOT_NONE.
     */
    if (occupier_id) {
        struct paranormal_entity *occupier = get_entity_by_id(occupier_id);
        slot_release(occupier);
        slot_occupy(occupier, e_slot_type, e_slot_id);
    }

    e->slot_type = s_type;
    e->slot_id = s_id;
    slots[s_type][s_id] = e->id;
}

void slot_release(struct paranormal_entity *e)
{
    if (e->slot_type != SLOT_NONE)
        *slots[e->slot_type - 1] = NO_ENTITY;
    e->slot_type = SLOT_NONE;
    e->slot_id = 0;
}

entity_id_t slot_get_occupier_id(enum slot_type s_type, uint8_t s_id)
{
    return slots[s_type][s_id];
}

bool slot_is_free(enum slot_type s_type, uint8_t s_id)
{
    return slot_get_occupier_id(s_type, s_id) == NO_ENTITY;
}

uint8_t slots_filter_free(enum slot_type s_type, uint8_t *s_ids, uint8_t n_ids)
{
    uint8_t nfree = 0;

    for (uint8_t i = 0; i < n_ids; i++) {
        if (slot_is_free(s_type, s_ids[i])) {
            s_ids[nfree++] = s_ids[i];
        }
    }
    return nfree;
}