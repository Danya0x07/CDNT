#ifndef _CORE_GAME_ROUTES_H
#define _CORE_GAME_ROUTES_H

#include "house.h"

enum route {
    ROUTE_1L_L,
    ROUTE_1R_L,
    ROUTE_3R_R,
    ROUTE_3L_R,

    NUM_OF_ROUTES
};

enum drawing read_next_drawing(enum route route, enum drawing current);
uint8_t find_closest_lamps(enum drawing d, enum room_light *rl);
void find_drawings_nearby(enum room_light rl, enum drawing *d);

#endif // _CORE_GAME_ROUTES_H