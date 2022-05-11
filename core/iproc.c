#include <iproc.h>

static const enum button_no btn_numbers[_BTNS_TOTAL] = 
        {BTN_NO_2, BTN_NO_7, BTN_NO_5, BTN_NO_6, BTN_NO_4, BTN_NO_3, BTN_NO_1};

enum joystick_event iproc_joystick(enum joystick_position pos)
{
    static enum joystick_position _pos = JPOS_CENTER;
    enum joystick_event ev = JEV_NOTHING;

    if (pos != _pos) {
        switch (pos) {
            case JPOS_UP:       ev = JEV_UP;    break;
            case JPOS_DOWN:     ev = JEV_DOWN;  break;
            case JPOS_LEFT:     ev = JEV_LEFT;  break;
            case JPOS_RIGHT:    ev = JEV_RIGHT; break;
            case JPOS_CENTER:
            default:
                break;
        }
        _pos = pos;
    }
    return ev;
}

uint8_t iproc_buttons(uint8_t b)
{
    static uint8_t _b = 0;
    uint8_t diff = b ^ _b;
    uint8_t ev = 0;

    for (uint8_t shift = 0; shift < 7; shift++) {
        if (b & diff & (1 << shift)) {
            ev |= btn_numbers[shift];
            break;
        }
    }

    for (uint8_t shift = 0; shift < 7; shift++) {
        if (~b & diff & (1 << shift)) {
            ev |= btn_numbers[shift] << 4;
            break;
        }
    }
    _b = b;
    return ev;
}