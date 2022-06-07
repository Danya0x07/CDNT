#include <game.h>

uint8_t __hour = 12;
uint8_t __pwr_consumption = 0;
uint8_t __score = 0;

bool game_is_active(void)
{

}

void game_enter(struct game_input *params)
{

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