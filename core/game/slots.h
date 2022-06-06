#ifndef _CORE_GAME_SLOTS_H
#define _CORE_GAME_SLOTS_H

#include <stdint.h>
#include <stdbool.h>
#include "entities.h"

enum __attribute__((packed)) slot_type {
    SLOT_NONE,
    SLOT_DRAWING,
    SLOT_LAMP,
    SLOT_CAM,
    SLOT_TV
};

void slot_occupy(entity_id entity, enum slot_type s_type, uint8_t s_idx);
void slot_release(entity_id entity);

entity_id slot_get_occupier(enum slot_type s_type, uint8_t s_idx);
bool slot_is_free(enum slot_type s_type, uint8_t s_idx);
uint8_t slots_filter_free(enum slot_type s_type, uint8_t *s_idxs, uint8_t n_idxs);

#endif // _CORE_GAME_SLOTS_H