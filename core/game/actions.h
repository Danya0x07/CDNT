#ifndef _CORE_GAME_ACTIONS_H
#define _CORE_GAME_ACTIONS_H

#include "entities.h"

typedef enum __attribute__((packed)) {
    ACT_SETUP,
    ACT_MOVE,
    ACT_EXORCISE,
    ACT_KICK_AWAY
} action_id;

void action_perform(action_id action, entity_id entity, void *arg);

#endif // _CORE_GAME_ACTIONS_H