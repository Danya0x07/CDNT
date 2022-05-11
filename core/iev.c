#include <iev.h>
#include <iproc.h>
#include <joystick.h>
#include <shiftreg.h>

enum joystick_event iev_poll_joystick(void)
{
    enum joystick_position pos = joystick_get_position();
    return iproc_joystick(pos);
}

uint8_t iev_poll_buttons(void)
{
    uint8_t b = shiftreg_read_buttons();
    return iproc_buttons(b);
}