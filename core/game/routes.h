#ifndef _CORE_GAME_ROUTES_H
#define _CORE_GAME_ROUTES_H

#include "house.h"

enum __attribute__((packed)) route_variant {
    ROUTEVAR_1L_L,
    ROUTEVAR_1R_L,
    ROUTEVAR_3R_R,
    ROUTEVAR_3L_R,

    NUM_OF_ROUTE_VARIANTS
};

enum drawing route_read_next(enum route_variant rvar, enum drawing current);
uint8_t find_closest_lamps(enum drawing d, enum room_lamp *rl);
void find_drawings_nearby(enum room_lamp rl, enum drawing *d);

#endif // _CORE_GAME_ROUTES_H