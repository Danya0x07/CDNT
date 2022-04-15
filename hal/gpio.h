#ifndef _HAL_GPIO_H
#define _HAL_GPIO_H

#include <avr/io.h>

typedef volatile uint8_t * gpio_t;

#define GPIOB   &PINB
#define GPIOC   &PINC
#define GPIOD   &PIND

#define _GPIO_PIN(gpio)     (gpio)
#define _GPIO_DDR(gpio)     ((gpio) + 1)
#define _GPIO_PORT(gpio)    ((gpio) + 2)

enum gpio_mode { GPIO_INPUT = 0, GPIO_OUTPUT = 1};

void gpio_set_mode(gpio_t gpio, uint8_t pin_no, enum gpio_mode mode);

#define gpio_write_high(gpio, pin_no)   (*_GPIO_PORT(gpio) |= _BV(pin_no))
#define gpio_write_low(gpio, pin_no)    (*_GPIO_PORT(gpio) &= ~_BV(pin_no))
#define gpio_toggle(gpio, pin_no)       (*_GPIO_PORT(gpio) ^= _BV(pin_no))
#define gpio_read(gpio, pin_no)     (!!bit_is_set(*_GPIO_PIN(gpio), pin_no))

#endif  // _HAL_GPIO_H