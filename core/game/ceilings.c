#include "ceilings.h"
#include <string.h>

static bool ceilings_statuses[NUM_OF_CEILINGS] = {OFF};

void ceiling_set(enum ceiling_no ceiling, bool status)
{
    ceilings_statuses[ceiling] = status;
}

bool ceiling_get(enum ceiling_no ceiling)
{
    return ceilings_statuses[ceiling];
}

void ceiling_toggle(enum ceiling_no ceiling)
{
    ceilings_statuses[ceiling] = !ceilings_statuses[ceiling];
}

void ceilings_off(void)
{
    memset(ceilings_statuses, OFF, sizeof(ceilings_statuses));
}
