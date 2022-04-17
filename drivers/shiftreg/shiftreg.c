#include "shiftreg.h"
#include <stddef.h>
#include <hal/spi.h>
#include <hal/gpio.h>
#include <hal/timers.h>

#define DRAWINGS_GPIO    GPIOD
#define LAMPS_GPIO       GPIOB
#define BUTTONS_GPIO     GPIOB

#define DRAWINGS_CS 7
#define LAMPS_CS    0
#define BUTTONS_CS  2
#define BUTTONS_PL  1

void shiftreg_init(void)
{
    gpio_set_mode(DRAWINGS_GPIO, DRAWINGS_CS, GPIO_OUTPUT);
    gpio_set_mode(LAMPS_GPIO, LAMPS_CS, GPIO_OUTPUT);
    gpio_set_mode(BUTTONS_GPIO, BUTTONS_CS, GPIO_OUTPUT);
    gpio_set_mode(BUTTONS_GPIO, BUTTONS_PL, GPIO_OUTPUT);

    uint8_t zeros[6] = {0};
    shiftreg_write_lamps(zeros);
    shiftreg_write_drawings(zeros);
}

void shiftreg_write_lamps(uint8_t content[static 4])
{
    gpio_write_low(LAMPS_GPIO, LAMPS_CS);
    spi_transfer_bytes(NULL, content, 4);
    gpio_write_high(LAMPS_GPIO, LAMPS_CS);
}

void shiftreg_write_drawings(uint8_t content[static 6])
{
    gpio_write_low(DRAWINGS_GPIO, DRAWINGS_CS);
    spi_transfer_bytes(NULL, content, 6);
    gpio_write_high(DRAWINGS_GPIO, DRAWINGS_CS);
}

uint8_t shiftreg_read_buttons(void)
{
    gpio_write_low(BUTTONS_GPIO, BUTTONS_PL);
    ms_wait(1);
    gpio_write_high(BUTTONS_GPIO, BUTTONS_PL);
    ms_wait(1);

    uint8_t content;
    gpio_write_low(BUTTONS_GPIO, BUTTONS_CS);
    content = spi_transfer_byte(0) & 0x7F;  // pin 7 unconnected
    gpio_write_high(BUTTONS_GPIO, BUTTONS_CS);
    return content;
}
