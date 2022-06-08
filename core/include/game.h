#ifndef _CORE_GAME_H
#define _CORE_GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <iev.h>

struct game_input {
    uint32_t moment;
    enum __attribute__((packed)) {
        GR_NEW_GAME,
        GR_CONTINUE
    } request;
    uint8_t night_no;
};

struct game_output {
    uint16_t hour;
    uint16_t score;
    enum __attribute__((packed)) {
        GS_PAUSE,
        GS_NIGHT_FAILED,
        GS_NIGHT_COMPLETED
    } status;
    uint8_t night_no;
};

bool game_is_active(void);
void game_enter(struct game_input *params);
void game_tick(enum joystick_event jev, uint8_t btnev, uint32_t t);
void game_get_results(struct game_output *results);

#endif // _CORE_GAME_H