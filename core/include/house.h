// House control interface.

#ifndef _CORE_HOUSE_H
#define _CORE_HOUSE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

enum __attribute__((packed)) ceiling_light {
    CEILING_L1,
    CEILING_L2,
    CEILING_L3,
    CEILING_L4,
    CEILING_L5,
    CEILING_L6,
    CEILING_L7
};

enum __attribute__((packed)) room_light {
    RL_R3_DESK,
    RL_R4_FLOOR,
    RL_R6_DESK,
    RL_R6_FLOOR,
    RL_R7_DESK,
    RL_R7_FLOOR,
};

enum __attribute__((packed)) camera_light {
    CAM_L1, CAM_L2, CAM_L3, CAM_L4, CAM_L5, CAM_L6, CAM_L7, CAM_LP
};

enum __attribute__((packed)) flash_light {
    FLASH_LIGHT_L,
    FLASH_LIGHT_R
};

enum __attribute__((packed)) drawing {
    DRAWING_R1L,
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

void ceiling_light_set(enum ceiling_light id, bool status);
void room_light_set(enum room_light id, bool status);
void camera_light_set(enum camera_light id, enum camera_mode mode);
void flash_light_set(enum flash_light id, enum flash_mode mode);
void drawing_set(enum drawing d, enum drawing_color c);
void tv_set(bool status);

void room_mask_set(uint8_t mask);

void house_reset(void);
void house_update(void);

#endif // _CORE_HOUSE_H