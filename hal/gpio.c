#include "gpio.h"

void gpio_set_mode(gpio_t gpio, uint8_t pin_no, enum gpio_mode mode)
{
    gpio = _GPIO_DDR(gpio);
    if (mode == GPIO_OUTPUT)
        *gpio |= _BV(pin_no);
    else
        *gpio &= ~_BV(pin_no);
}
