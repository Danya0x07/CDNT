#ifndef _CORE_GAME_TMEV_H
#define _CORE_GAME_TMEV_H

#include <stdint.h>
#include <stdbool.h>

struct timeout_event {
    uint32_t timeout;
    uint32_t _last_exec_time;
    void (*callback)(void);
    bool active;
    bool periodic;
};

void timeout_event_init(struct timeout_event *tmev, uint32_t t);
bool timeout_event_check(struct timeout_event *tmev, uint32_t t);

#endif // _CORE_GAME_TMEV_H