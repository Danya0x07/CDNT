#include "routes.h"

#include <avr/pgmspace.h>

static const PROGMEM enum drawing route_1l_l[NUM_OF_DRAWINGS] = {
    [DRAWING_R1L] = DRAWING_R3R,
    [DRAWING_R1R] =     DRAWING_R1L,
    [DRAWING_R2L] =     DRAWING_R1R,
    [DRAWING_R2R] =     DRAWING_R2L,
    [DRAWING_R3L] = DRAWING_R4L,
    [DRAWING_R3R] = DRAWING_R3L,
    [DRAWING_R4L] = DRAWING_R4R,
    [DRAWING_R4R] = DRAWING_R5M,
    [DRAWING_R5M] = DRAWING_R6R,
    [DRAWING_R6L] = DRAWING_RPL,
    [DRAWING_R6R] = DRAWING_R6L,
    [DRAWING_R7B] =     DRAWING_R5M,
    [DRAWING_R7F] =     DRAWING_R7B,
    [DRAWING_RPL] = DRAWING_RPM,
    [DRAWING_RPR] =     DRAWING_RPM,
    [DRAWING_RPM] =     DRAWING_RPM,
};

static const PROGMEM enum drawing route_1r_l[NUM_OF_DRAWINGS] = {
    [DRAWING_R1L] =     DRAWING_R1R,
    [DRAWING_R1R] = DRAWING_R2L,
    [DRAWING_R2L] = DRAWING_R2R,
    [DRAWING_R2R] = DRAWING_R7F,
    [DRAWING_R3L] =     DRAWING_R3R,
    [DRAWING_R3R] =     DRAWING_R1L,
    [DRAWING_R4L] =     DRAWING_R3L,
    [DRAWING_R4R] =     DRAWING_R4L,
    [DRAWING_R5M] = DRAWING_R6R,
    [DRAWING_R6L] = DRAWING_RPL,
    [DRAWING_R6R] = DRAWING_R6L,
    [DRAWING_R7B] = DRAWING_R5M,
    [DRAWING_R7F] = DRAWING_R7B,
    [DRAWING_RPL] = DRAWING_RPM,
    [DRAWING_RPR] =     DRAWING_RPM,
    [DRAWING_RPM] =     DRAWING_RPM,
};

static const PROGMEM enum drawing route_3r_r[NUM_OF_DRAWINGS] = {
    [DRAWING_R1L] = DRAWING_R1R,
    [DRAWING_R1R] = DRAWING_R2L,
    [DRAWING_R2L] = DRAWING_R2R,
    [DRAWING_R2R] = DRAWING_R7F,
    [DRAWING_R3L] =     DRAWING_R3R,
    [DRAWING_R3R] = DRAWING_R1L,
    [DRAWING_R4L] =     DRAWING_R3L,
    [DRAWING_R4R] =     DRAWING_R4L,
    [DRAWING_R5M] =     DRAWING_R4R,
    [DRAWING_R6L] =     DRAWING_R6R,
    [DRAWING_R6R] =     DRAWING_R5M,
    [DRAWING_R7B] =     DRAWING_R7F,
    [DRAWING_R7F] = DRAWING_RPR,
    [DRAWING_RPL] =     DRAWING_RPM,
    [DRAWING_RPR] = DRAWING_RPM,
    [DRAWING_RPM] =     DRAWING_RPM,
};

static const PROGMEM enum drawing route_3l_r[NUM_OF_DRAWINGS] = {
    [DRAWING_R1L] =     DRAWING_R3R,
    [DRAWING_R1R] =     DRAWING_R1L,
    [DRAWING_R2L] =     DRAWING_R1R,
    [DRAWING_R2R] =     DRAWING_R2L,
    [DRAWING_R3L] = DRAWING_R4L,
    [DRAWING_R3R] =     DRAWING_R3L,
    [DRAWING_R4L] = DRAWING_R4R,
    [DRAWING_R4R] = DRAWING_R5M,
    [DRAWING_R5M] = DRAWING_R7B,
    [DRAWING_R6L] =     DRAWING_R6R,
    [DRAWING_R6R] =     DRAWING_R5M,
    [DRAWING_R7B] = DRAWING_R7F,
    [DRAWING_R7F] = DRAWING_RPR,
    [DRAWING_RPL] =     DRAWING_RPM,
    [DRAWING_RPR] = DRAWING_RPM,
    [DRAWING_RPM] =     DRAWING_RPM,
};

static const PROGMEM enum drawing *const routes[NUM_OF_ROUTES] = 
    {route_1l_l, route_1r_l, route_3r_r, route_3l_r};

enum drawing read_next_drawing(enum route route, enum drawing current)
{
    return pgm_read_byte(pgm_read_word(&routes[route]) + current);
}

uint8_t find_closest_lamps(enum drawing d, enum room_light *rl)
{
    uint8_t nlamps = 0;

    switch (d) {
        default:
            break;
        
        case DRAWING_R3R:
        case DRAWING_R3L:
            rl[0] = RL_R3_DESK;
            nlamps = 1;
            break;
        
        case DRAWING_R4L:
            rl[0] = RL_R3_DESK;
            rl[1] = RL_R4_FLOOR;
            nlamps = 2;
            break;
        
        case DRAWING_R4R:
            rl[0] = RL_R4_FLOOR;
            nlamps = 1;
            break;
        
        case DRAWING_R5M:
            rl[0] = RL_R6_FLOOR;
            nlamps = 1;
            break;
        
        case DRAWING_R6L:
        case DRAWING_R6R:
            rl[0] = RL_R6_FLOOR;
            rl[1] = RL_R6_DESK;
            nlamps = 2;
            break;
        
        case DRAWING_R2R:
            rl[0] = RL_R7_FLOOR;
            nlamps = 1;
            break;
        
        case DRAWING_R7B:
        case DRAWING_R7F:
            rl[0] = RL_R7_FLOOR;
            rl[1] = RL_R7_DESK;
            nlamps = 2;
            break;
    }
    return nlamps;
}

static const PROGMEM enum drawing dr_next_to_rl[NUM_OF_ROOM_LIGHTS][3] = {
    [RL_R3_DESK]  = {DRAWING_R3R, DRAWING_R3L, DRAWING_R4L},
    [RL_R4_FLOOR] = {DRAWING_R4L, DRAWING_R4R, DRAWING_R5M},
    [RL_R6_DESK]  = {DRAWING_R6R, DRAWING_R6L, DRAWING_RPL},
    [RL_R6_FLOOR] = {DRAWING_R5M, DRAWING_R6R, DRAWING_R6L},
    [RL_R7_DESK]  = {DRAWING_R5M, DRAWING_R7B, DRAWING_R7F},
    [RL_R7_FLOOR] = {DRAWING_R7B, DRAWING_R7F, DRAWING_R2R}
};

void find_drawings_nearby(enum room_light rl, enum drawing *d)
{
    d[0] = pgm_read_byte(&dr_next_to_rl[rl][0]);
    d[1] = pgm_read_byte(&dr_next_to_rl[rl][1]);
    d[2] = pgm_read_byte(&dr_next_to_rl[rl][2]);
}