#ifndef _CORE_GAME_H
#define _CORE_GAME_H

#include <stdint.h>

struct game_input {
    enum __attribute__((packed)) {
        NEW_GAME,
        CONTINUE
    } action;
    union {
        uint8_t night_no;
    };
};

struct game_output {
    enum __attribute__((packed)) {
        PAUSE,
        GAME_OVER,
        NIGHT_COMPLETED
    } status;
};

#endif // _CORE_GAME_H