#ifndef _CORE_GAME_SLOTS_H
#define _CORE_GAME_SLOTS_H

#include <stdint.h>

enum __attribute__((packed)) slot_type {
    SLOT_NONE,
    SLOT_DRAWING,
    SLOT_LAMP,
    SLOT_CAM,
    SLOT_TV
};

struct paranormal_entity;

void slot_occupy(struct paranormal_entity *e, enum slot_type s_type, uint8_t s_id);
void slot_release(struct paranormal_entity *e);

entity_id_t slot_get_occupier_id(enum slot_type s_type, uint8_t s_id);
bool slot_is_free(enum slot_type s_type, uint8_t s_id);
uint8_t slots_filter_free(enum slot_type s_type, uint8_t *s_ids, uint8_t n_ids);

#endif // _CORE_GAME_SLOTS_H