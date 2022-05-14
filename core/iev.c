#include <iev.h>
#include <iproc.h>
#include <joystick.h>
#include <shiftreg.h>
#include <hal/timers.h>

#define JOYSTICK_POLL_PERIOD    50

enum joystick_event iev_poll_joystick(void)
{
    static uint32_t now = 0;

    if (ms_passed() - now >= JOYSTICK_POLL_PERIOD) {
        enum joystick_position pos = joystick_get_position();
        now = ms_passed();
        return iproc_joystick(pos);
    }
    return JEV_NOTHING;
}

uint8_t iev_poll_buttons(void)
{
    uint8_t b = shiftreg_read_buttons();
    return iproc_buttons(b);
}