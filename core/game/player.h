#ifndef _CORE_GAME_PLAYER_H
#define _CORE_GAME_PLAYER_H

#include <iev.h>
#include <house.h>

struct player_request {
    enum __attribute__((packed)) {
        PR_NOTHING,
        PR_WFLASH_L,
        PR_WFLASH_R,
        PR_UVFLASH,
        PR_CEILING_TG,
        PR_LAMP_OFF,
        PR_TV_OFF,
        PR_SELECT_CAM,
        PR_UV_ON,
        PR_UV_OFF,
        PR_PAUSE
    } type;
    union {
        enum ceiling ceiling;
        enum room_lamp lamp;
        enum camera_no cam;
    };
};

struct player_request request_get(enum joystick_event jev, uint8_t btnev, enum camera_no cam);

#endif // _CORE_GAME_PLAYER_H