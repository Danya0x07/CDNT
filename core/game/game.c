#include <game.h>
#include <graphics.h>
#include <house.h>
#include "entity.h"

bool __ceilings_on[NUM_OF_CEILINGS] = {0};

uint8_t __hour = 12;
uint8_t __pwr_consumption = 0;
uint8_t __score = 0;

enum camera_light __cam = CAM_LP;
enum camera_mode __cam_mode = CAM_MODE_W;

bool dummy = false;

bool game_is_active(void)
{
    return dummy;
}

void game_enter(struct game_input *params)
{
    dummy = true;
}

void game_tick(enum joystick_event jev, uint8_t btnev, uint32_t t)
{
    // Process user events

    // Proces time-dependent events

    // Process game data

    // Update view

}

void game_get_results(struct game_output *results)
{
    
}