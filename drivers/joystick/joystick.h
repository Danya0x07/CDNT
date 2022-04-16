#ifndef _JOYSTICK_H
#define _JOYSTICK_H

enum joystick_position {
    JPOS_CENTER = 0,
    JPOS_UP,
    JPOS_DOWN,
    JPOS_LEFT,
    JPOS_RIGHT
};

enum joystick_position joystick_get_position(void);

#endif  // _JOYSTICK_H