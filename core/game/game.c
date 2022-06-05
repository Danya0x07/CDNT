#include <game.h>
#include <graphics.h>

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