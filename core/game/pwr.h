#ifndef _CORE_GAME_PWR_H
#define _CORE_GAME_PWR_H

#include "tmev.h"

enum __attribute__((packed)) pwr_status {
    PWR_OFF,
    PWR_ON
};

void pwr_init(void);
void pwr_update();
uint8_t pwr_consumption_get(void);
bool pwr_consumption_exceeds(void);
enum pwr_status pwr_status_get(void);

extern struct timeout_event tmev_pwr_kill;
extern struct timeout_event tmev_pwr_restore;

#endif // _CORE_GAME_PWR_H