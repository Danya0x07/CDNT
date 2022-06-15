#include <string.h>
#include <music.h>
#include <tracks.h>

#include "ceilings.h"

static bool ceilings_statuses[NUM_OF_CEILINGS] = {OFF};

void ceiling_set(enum ceiling ceiling, bool status)
{
    ceilings_statuses[ceiling] = status;
}

bool ceiling_get(enum ceiling ceiling)
{
    return ceilings_statuses[ceiling];
}

void ceiling_toggle(enum ceiling ceiling)
{
    ceilings_statuses[ceiling] = !ceilings_statuses[ceiling];
    music_start(ceiling_get(ceiling) ? &track_lamps_on: &track_lamps_off);
}

void ceilings_off(void)
{
    memset(ceilings_statuses, OFF, sizeof(ceilings_statuses));
}
