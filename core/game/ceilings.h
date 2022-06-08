#ifndef _CORE_GAME_CEILINGS_H
#define _CORE_GAME_CEILINGS_H

#include <house.h>

void ceiling_set(enum ceiling ceiling, bool status);
bool ceiling_get(enum ceiling ceiling);
void ceiling_toggle(enum ceiling ceiling);
void ceilings_off(void);

#endif // _CORE_GAME_CEILINGS_H