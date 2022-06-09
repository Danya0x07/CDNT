#include "setup.h"
#include "entities.h"
#include <config.h>

#include <avr/pgmspace.h>

static const PROGMEM uint8_t night_activities[NIGHTS_MAX][NUM_OF_ENTITIES] = {
    {0, 0, 0, 0, 20},
    {4, 3, 2, 0, 0},
    {0, 0, 0, 20, 0},
    {8, 7, 9, 6, 8},
    {10, 9, 14, 10, 12}
};

uint8_t custom_activities[NUM_OF_ENTITIES];

void setup_entities(uint8_t night_no)
{
    if (night_no) {
        uint8_t idx = night_no - 1;
        for (entity_id e = _ENTITY_FIRST; e <= NUM_OF_ENTITIES; e++) {
            entity_setup(e, pgm_read_byte(&night_activities[idx][e - 1]));
        }
    } else {
        for (entity_id e = _ENTITY_FIRST; e <= NUM_OF_ENTITIES; e++) {
            entity_setup(e, custom_activities[e - 1]);
        }
    }
}