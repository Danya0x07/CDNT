#ifndef _CORE_GAME_H
#define _CORE_GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <iev.h>

struct game_input {
    enum __attribute__((packed)) {
        ACTION_NEW_GAME,
        ACTION_CONTINUE
    } action;
    uint8_t night_no;
};

struct game_output {
    enum __attribute__((packed)) {
        GS_PAUSE,
        GS_NIGHT_FAILED,
        GS_NIGHT_COMPLETED
    } status;
    uint16_t hours_survived;
    uint8_t night_no;
    uint8_t attacks_repelled;
};

bool game_is_active(void);
void game_enter(struct game_input *params);
void game_tick(enum joystick_event jev, uint8_t btnev, uint32_t t);
void game_get_results(struct game_output *results);

#endif // _CORE_GAME_H