#include <game.h>

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
    dummy = false;
}

void game_get_results(struct game_output *results)
{
    results->attacks_repelled = 5;
    results->hours_survived = 4;
}