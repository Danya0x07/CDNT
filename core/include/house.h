// House control interface.

#ifndef _CORE_HOUSE_H
#define _CORE_HOUSE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

enum __attribute__((packed)) ceiling {
    _CEILING_FIRST = 0,

    CEILING1 = _CEILING_FIRST,
    CEILING2,
    CEILING3,
    CEILING4,
    CEILING5,
    CEILING6,
    CEILING7,

    NUM_OF_CEILINGS
};

enum __attribute__((packed)) room_lamp {
    _RL_FIRST = 0,

    RL_R3_DESK = _RL_FIRST,
    RL_R4_FLOOR,
    RL_R6_DESK,
    RL_R6_FLOOR,
    RL_R7_DESK,
    RL_R7_FLOOR,

    NUM_OF_ROOM_LAMPS
};

enum __attribute__((packed)) camera {
    CAM1, CAM2, CAM3, CAM4, CAM5, CAM6, CAM7, CAMP,
    NUM_OF_CAMS
};

enum __attribute__((packed)) flash {
    FLASH_L,
    FLASH_R
};

enum __attribute__((packed)) drawing {
    _DRAWING_FIRST = 0,

    DRAWING_R1L = _DRAWING_FIRST,
    DRAWING_R1R,
    DRAWING_R2L,
    DRAWING_R2R,
    DRAWING_R3L,
    DRAWING_R3R,
    DRAWING_R4L,
    DRAWING_R4R,
    DRAWING_R5M,
    DRAWING_R6L,
    DRAWING_R6R,
    DRAWING_R7B,
    DRAWING_R7F,
    DRAWING_RPL,
    DRAWING_RPR,
    DRAWING_RPM,

    NUM_OF_DRAWINGS,
};

enum __attribute__((packed)) camera_mode {
    CAM_MODE_OFF,
    CAM_MODE_W,
    CAM_MODE_UV
};

enum __attribute__((packed)) flash_mode {
    FLASH_MODE_OFF,
    FLASH_MODE_W,
    FLASH_MODE_UV
};

enum __attribute__((packed)) drawing_color {
    DCOLOR_OFF,
    DCOLOR_RED,
    DCOLOR_GREEN,
    DCOLOR_YELLOW,
    DCOLOR_BLUE,
    DCOLOR_PURPLE,
    DCOLOR_CYAN,
    DCOLOR_WHITE
};

enum __attribute__((packed)) {
    MASK_ROOM1 = (1 << 0),
    MASK_ROOM2 = (1 << 1),
    MASK_ROOM3 = (1 << 2),
    MASK_ROOM4 = (1 << 3),
    MASK_ROOM5 = (1 << 4),
    MASK_ROOM6 = (1 << 5),
    MASK_ROOM7 = (1 << 6),
    MASK_ROOMP = (1 << 7),
    MASK_FLOOR1 = MASK_ROOM1 | MASK_ROOM2 | MASK_ROOM3,
    MASK_FLOOR2 = MASK_ROOM4 | MASK_ROOM5 | MASK_ROOM6 | MASK_ROOM7,
    MASK_ALL = MASK_FLOOR1 | MASK_FLOOR2 | MASK_ROOMP
};

#define OFF  false
#define ON   true

void ceiling_light_set(enum ceiling c, bool status);
void lamp_light_set(enum room_lamp rl, bool status);
void camera_light_set(enum camera c, enum camera_mode mode);
void flash_light_set(enum flash f, enum flash_mode mode);
void drawing_light_set(enum drawing d, enum drawing_color c);
void tv_noise_set(bool status);

void room_mask_set(uint8_t mask);

void house_reset(void);
void house_update(void);

#endif // _CORE_HOUSE_H