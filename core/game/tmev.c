#include "tmev.h"

void timeout_event_init(struct timeout_event *tmev, uint32_t t)
{
    tmev->_last_exec_time = t;
    tmev->active = true;
}

bool timeout_event_check(struct timeout_event *tmev, uint32_t t, void *arg)
{
    if (tmev->active && t - tmev->_last_exec_time >= tmev->timeout) {
        tmev->callback(arg);
        tmev->_last_exec_time = t;
        if (!tmev->periodic)
            tmev->active = false;
        return true;
    }
    return false;
}