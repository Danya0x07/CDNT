#include "st7735.h"
#include <hal/gpio.h>
#include <hal/timers.h>
#include <hal/spi.h>

// Display GPIO pins definition
#define DRIVER_GPIO GPIOD
#define DRIVER_CS   5
#define DRIVER_DC   4
#define DRIVER_RST  3

/* Commands definition.
 * As the command table is huge, only necessary commands are defined. */
#define CMD_NOP 0x00
#define CMD_CASET   0x2A
#define CMD_RASET   0x2B
#define CMD_RAMWR   0x2C
#define CMD_SLPIN   0x10
#define CMD_SLPOUT  0x11
#define CMD_INVOFF  0x20
#define CMD_INVON   0x21
#define CMD_GAMSET  0x26
#define CMD_DISPOFF 0x28
#define CMD_DISPON  0x29
#define CMD_MADCTL  0x36
#define CMD_COLMOD  0x3A
#define CMD_FRMCTR1 0xB1

// Color format options.
#define COLMOD_RGB444   3
#define COLMOD_RGB565   5
#define COLMOD_RGB666   6

static void send_cmd(uint8_t cmd)
{
    gpio_write_low(DRIVER_GPIO, DRIVER_DC);
    gpio_write_low(DRIVER_GPIO, DRIVER_CS);
    spi_transfer_byte(cmd);
    gpio_write_high(DRIVER_GPIO, DRIVER_CS);
    gpio_write_high(DRIVER_GPIO, DRIVER_DC);
}

static void send_data(uint8_t b)
{
    gpio_write_low(DRIVER_GPIO, DRIVER_CS);
    spi_transfer_byte(b);
    gpio_write_high(DRIVER_GPIO, DRIVER_CS);
}

static void reset(void)
{
    gpio_write_low(DRIVER_GPIO, DRIVER_RST);
    ms_wait(1);
    gpio_write_high(DRIVER_GPIO, DRIVER_RST);
    ms_wait(120);
}

void st7735_init(void)
{
    gpio_set_mode(DRIVER_GPIO, DRIVER_CS, GPIO_OUTPUT);
    gpio_set_mode(DRIVER_GPIO, DRIVER_DC, GPIO_OUTPUT);
    gpio_set_mode(DRIVER_GPIO, DRIVER_RST, GPIO_OUTPUT);
    gpio_write_high(DRIVER_GPIO, DRIVER_CS);
    gpio_write_high(DRIVER_GPIO, DRIVER_DC);
    gpio_write_high(DRIVER_GPIO, DRIVER_RST);

    reset();
    send_cmd(CMD_SLPOUT);
    send_cmd(CMD_SLPOUT);
    ms_wait(20);
    send_cmd(CMD_COLMOD);
    send_data(COLMOD_RGB565);
    send_cmd(CMD_MADCTL);
    send_data(0xA0);  // orientation

    // Adjust FPS
    send_cmd(CMD_FRMCTR1);
    send_data(0x00);
    send_data(0x0F);
    send_data(0x00);
    send_data(0x0F);
    send_data(0x00);
    send_data(0x0F);

    // Enable display
    send_cmd(CMD_DISPON);
}

void st7735_set_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    send_cmd(CMD_CASET);
    send_data(0);
    send_data(x0);
    send_data(0);
    send_data(x1);

    send_cmd(CMD_RASET);
    send_data(0);
    send_data(y0);
    send_data(0);
    send_data(y1);
}

void st7735_start_ram_write(void)
{
    send_cmd(CMD_RAMWR);
}

void st7735_write_pixel(uint16_t color)
{
    send_data((uint8_t)(color >> 8));
    send_data((uint8_t)color);
}

void st7735_set_gamma_curve(enum st7735_gamma_curve curve)
{
    send_cmd(CMD_GAMSET);
    send_data(curve);
}

void st7735_display_off(void)
{
    send_cmd(CMD_DISPOFF);
}

void st7735_display_on(void)
{
    send_cmd(CMD_DISPON);
}

void st7735_set_inverse(bool inverse)
{
    send_cmd(inverse ? CMD_INVON : CMD_INVOFF);
}