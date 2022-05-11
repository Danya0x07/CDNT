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
    _BTN_FIRST = 1,

    BTN_1 = 1,
    BTN_2,
    BTN_3,
    BTN_4,
    BTN_5,
    BTN_6,
    BTN_7,

    _BTN_LAST = BTN_7,
    _BTNS_TOTAL = _BTN_LAST
};

#define PRESSED_BUTTON(evbyte)  ((evbyte) & 0x0F)
#define RELEASED_BUTTON(evbyte) ((evbyte) >> 4)

enum joystick_event iev_poll_joystick(void);
uint8_t iev_poll_buttons(void);

#endif // _CORE_IEV_H