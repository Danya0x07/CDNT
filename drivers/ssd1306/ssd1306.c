#include "ssd1306.h"
#include <hal/i2c.h>

#define SSD1306_ADDRESS 0x78

// Control byte variants
#define TREAT_NEXT_AS_CMD   0x80
#define TREAT_NEXT_AS_DATA  0xC0
#define TREAT_REST_AS_CMD   0x00
#define TREAT_REST_AS_DATA  0x40

// Commands for page addressing mode
#define CMD_SET_START_COL_H 0x00
#define CMD_SET_START_COL_L 0x10
#define CMD_SET_START_PAGE  0xB0

#define CMD_SET_ADDRESSING_MODE 0x20
#define ADDR_MODE_HORIZONTAL    0
#define ADDR_MODE_VERTICAL      1
#define ADDR_MODE_PAGE          2

// Commands for H and V addressing modes
#define CMD_SET_PAGE    0x22
#define CMD_SET_COL     0x21

// Setup commands
#define CMD_SET_CONTRAST    0x81
#define CMD_PIXELS_NORMAL   0xA4
#define CMD_ALL_PIXELS_ON   0xA5
#define CMD_CONTENT_NORMAL  0xA6
#define CMD_CONTENT_INVERSE 0xA7
#define CMD_DISPLAY_OFF 0xAE
#define CMD_DISPLAY_ON  0xAF

// Layout commands
#define CMD_SET_START_LINE  0x40
#define CMD_SET_SEGMENT_REMAP   0xA0
#define CMD_SET_MULTIPLEX_RATIO 0xA8
#define CMD_COM_SCAN_DIR_INC    0xC0
#define CMD_COM_SCAN_DIR_DEC    0xC8
#define CMD_SET_DISPLAY_OFFSET  0xD3
#define CMD_SET_COM_PINS    0xDA

// Timing commands
#define CMD_SET_DISPLAY_CLOCK_DIV_RATIO 0xD5
#define CMD_SET_PRECHARGE_PERIOD    0xD9
#define CMD_SET_VCOM_DESELECT   0xDB
#define CMD_NOP 0xE3

// Charge pump commands
#define CMD_CONFIG_CHARGE_PUMP  0x8D
#define CHARGE_PUMP_ENABLE  0x14
#define CHARGE_PUMP_DISABLE 0x10

// Scrolling commands
#define CMD_H_SCROLL_R  0x26
#define CMD_H_SCROLL_L  0x27
#define CMD_HV_SCROLL_R 0x29
#define CMD_HV_SCROLL_L 0x2A
#define CMD_DEACTIVATE_SCROLL   0x2E
#define CMD_ACTIVATE_SCROLL 0x2F
#define CMD_SET_V_SCROLL_AREA   0xA3

static const uint8_t init_sequence[] = {
    CMD_DISPLAY_OFF,
    CMD_SET_DISPLAY_CLOCK_DIV_RATIO, 0xF0,
    CMD_SET_MULTIPLEX_RATIO, 0x3F,
    CMD_SET_DISPLAY_OFFSET, 0x0,
    CMD_SET_START_LINE | 0x0,
    CMD_CONFIG_CHARGE_PUMP, CHARGE_PUMP_ENABLE,
    CMD_SET_ADDRESSING_MODE, ADDR_MODE_HORIZONTAL,
    CMD_SET_SEGMENT_REMAP | 0x1,
    CMD_COM_SCAN_DIR_DEC,
    CMD_SET_COM_PINS, 0x12,
    CMD_SET_CONTRAST, 0xFF,
    CMD_SET_PRECHARGE_PERIOD, 0xF1,
    CMD_SET_VCOM_DESELECT, 0x40,
    CMD_PIXELS_NORMAL,
    CMD_CONTENT_NORMAL,
    CMD_DISPLAY_ON,
};

static void send_cmd(uint8_t cmd)
{
    i2c_start(SSD1306_ADDRESS, I2C_DIRECTION_TX);
    i2c_write_byte(TREAT_NEXT_AS_CMD);
    i2c_write_byte(cmd);
    i2c_stop();
}

void ssd1306_init(void)
{
    for (uint8_t i = 0; i < sizeof(init_sequence); i++) {
        send_cmd(init_sequence[i]);
    }
    ssd1306_clear();
}

void ssd1306_set_cursor(uint8_t page, uint8_t column)
{
    send_cmd(CMD_SET_PAGE);
    send_cmd(page & 0x7);
    send_cmd(0x7);

    send_cmd(CMD_SET_COL);
    send_cmd(column & 0x7F);
    send_cmd(0x7F);
}

void ssd1306_begin_write(void)
{
    i2c_start(SSD1306_ADDRESS, I2C_DIRECTION_TX);
    i2c_write_byte(TREAT_REST_AS_DATA);
}

void ssd1306_write_byte(uint8_t b)
{
    i2c_write_byte(b);
}

void ssd1306_end_write(void)
{
    i2c_stop();
}

void ssd1306_clear(void)
{
    i2c_start(SSD1306_ADDRESS, I2C_DIRECTION_TX);
    i2c_write_byte(TREAT_REST_AS_DATA);
    for (uint16_t i = 0; i < 128 * 8; i++)
        i2c_write_byte(0);
    i2c_stop();
}

void ssd1306_display_off(void)
{
    send_cmd(CMD_DISPLAY_OFF);
}

void ssd1306_display_on(void)
{
    send_cmd(CMD_DISPLAY_ON);
}

void ssd1306_set_inverse(bool inverse)
{
    send_cmd(inverse ? CMD_CONTENT_INVERSE : CMD_CONTENT_NORMAL);
}

void ssd1306_start_scrolling(void)
{
    const uint8_t setup_sequence[] = {
        CMD_H_SCROLL_L,
        0x00, // dummy byte
        0, 7, 7,
        0, 0xFF
    };
    for (uint8_t i = 0; i < sizeof(setup_sequence); i++)
        send_cmd(setup_sequence[i]);
    //i2c_write_bytes(SSD1306_ADDRESS, setup_sequence, sizeof(setup_sequence), 0);
    send_cmd(CMD_ACTIVATE_SCROLL);
}

void ssd1306_stop_scrolling(void)
{
    send_cmd(CMD_DEACTIVATE_SCROLL);
}
