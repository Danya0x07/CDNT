#ifndef _CORE_IEV_H
#define _CORE_IEV_H

#include <stdint.h>

enum __attribute__((packed)) joystick_event {
    JEV_NOTHING = 0,
    JEV_UP,
    JEV_DOWN,
    JEV_LEFT,
    JEV_RIGHT
};

enum __attribute__((packed)) button_no {
    _BTN_NO_FIRST = 1,

    BTN_NO_1 = 1,
    BTN_NO_2,
    BTN_NO_3,
    BTN_NO_4,
    BTN_NO_5,
    BTN_NO_6,
    BTN_NO_7,

    _BTN_NO_LAST = BTN_NO_7,
    _BTNS_TOTAL = _BTN_NO_LAST
};

#define PRESSED_BUTTON(evbyte)  ((evbyte) & 0x0F)
#define RELEASED_BUTTON(evbyte) ((evbyte) >> 4)

#endif // _CORE_IEV_H