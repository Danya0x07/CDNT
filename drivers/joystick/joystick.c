#include "joystick.h"
#include <hal/adc.h>

#define CHANNEL_X   6
#define CHANNEL_Y   7

#define LOW_BORDER  (512 - 200)
#define HIGH_BORDER (512 + 200)

enum joystick_position joystick_get_position(void)
{
    uint16_t x = adc_measure(CHANNEL_X);
    uint16_t y = adc_measure(CHANNEL_Y);

    if (x < LOW_BORDER)
        return JPOS_LEFT;
    if (x > HIGH_BORDER)
        return JPOS_RIGHT;
    if (y < LOW_BORDER)
        return JPOS_DOWN;
    if (y > HIGH_BORDER)
        return JPOS_UP;
    return JPOS_CENTER;
}