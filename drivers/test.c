#include <stdlib.h>

#include <avr/interrupt.h>

#include <hal/adc.h>
#include <hal/spi.h>
#include <hal/i2c.h>
#include <hal/timers.h>
#include <hal/uart.h>

#include <joystick.h>
#include <serial.h>
#include <shiftreg.h>
#include <ssd1306.h>
#include <st7735.h>

void system_init(void)
{
    adc_init();
    spi_init();
    i2c_init();
    timers_init();
    uart_init();
    sei();

    shiftreg_init();
    ssd1306_init();
    st7735_init();
}

void test_lamps()
{
    serial_print_str("Testing lamps!\n");
    uint8_t data[4] = {0};

    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            data[i] |= 1 << (7 - j);
            shiftreg_write_lamps(data);
            ms_wait(500);
            data[i] &= ~(1 << (7 - j));
            shiftreg_write_lamps(data);
            ms_wait(500);
        }
    }
}

void test_drawings()
{
    serial_print_str("Testing drawings!\n");
    uint8_t data[6] = {0};

    for (uint8_t i = 0; i < 6; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            data[i] |= 1 << (7 - j);
            shiftreg_write_drawings(data);
            ms_wait(500);
            data[i] &= ~(1 << (7 - j));
            shiftreg_write_drawings(data);
            ms_wait(500);
        }
    }
}

void test_buttons(void)
{
    serial_print_str("Testing buttons!\n");
    uint16_t data = 0;
    for (;;) {
        data = shiftreg_read_buttons();
        serial_print_hex(data);
        serial_print_str("\n--------\n");
        ms_wait(1000);
    }
}

void test_joystick(void)
{
    serial_print_str("Testing joystick!\n");
    const char *const dirs[5] = 
        {"CENTER", "UP", "DOWN", "LEFT", "RIGHT"};
    uint16_t pos = 0;

    for (;;) {
        pos = adc_measure(6);
        serial_print_dec(pos);
        serial_print_char('\t');
        pos = adc_measure(7);
        serial_print_dec(pos);
        serial_print_char('\t');
        pos = joystick_get_position();
        serial_print_str(dirs[pos]);
        serial_print_str("\n--------\n");
        ms_wait(300);
    }
}

void test_serial_receiving(void)
{
    for (;;) {
        if (serial_line_received()) {
            char buff[64] = {0};
            uint8_t len = serial_read_line(buff);
            serial_print_dec(len);
            serial_print_char(' ');
            serial_print_str(buff);
            serial_print_char('\n');
        }
        ms_wait(500);
    }
}

void test_buzzer_playing(void)
{
    serial_print_str("Testing buzzer!\n");

    meander_start(440);
    ms_wait(1000);
    meander_stop();

    uint32_t now = 0;

    for (uint16_t f = 200; f < 2001; f += 200) {
        serial_print_str("\n---------\n");
        serial_print_dec(f);
        serial_print_str(" (Hz)\n");
        meander_emit(f, 1000);
        while (meander_emitting()) {
            if (ms_passed() - now >= 200) {
                serial_print_char('.');
                now = ms_passed();
            }
        }
    }
}

void test_oled_display(void)
{
    serial_print_str("Testing OLED display!\n");

    ssd1306_begin_write();
    for (uint16_t i = 0; i < 128 * 8; i++) {
        ssd1306_write_byte(0xAA & rand());
    }
    ssd1306_end_write();
    ms_wait(3000);
    ssd1306_display_off();
    ms_wait(3000);
    ssd1306_display_on();

    ssd1306_start_scrolling();
}

void test_tft_display(void)
{
    serial_print_str("Testing TFT display!\n");

    st7735_set_window(10, 10, ST7735_MAX_X - 20, ST7735_MAX_Y - 30);

    uint16_t color = 0xFFFF;
    st7735_start_ram_write();
    do {
        st7735_write_pixel(color--);
    } while (color);
    ms_wait(2000);
    st7735_display_off();
    ms_wait(2000);
    st7735_display_on();

    for (uint8_t i = 0; i < 5; i++) {
        ms_wait(2000);
        st7735_set_inverse(i & 1);
    }
    ms_wait(6000);
    meander_emit(440, 100);
    st7735_set_gamma_curve(ST7735_GAMMA_1_0);
    ms_wait(6000);
    meander_emit(440, 100);
    st7735_set_gamma_curve(ST7735_GAMMA_1_8);
    ms_wait(6000);
    meander_emit(440, 100);
    st7735_set_gamma_curve(ST7735_GAMMA_2_2);
    ms_wait(6000);
    meander_emit(440, 100);
    st7735_set_gamma_curve(ST7735_GAMMA_2_5);
}

int main(void)
{
    system_init();

    serial_print_str("What are we going to test?\t");
    while (uart_rx_buffer_empty()) {}
    char cmd = uart_read_byte();

    switch (cmd) {
        case 'l': test_lamps();     break;
        case 'd': test_drawings();  break;
        case 'b': test_buttons();   break;
        case 'j': test_joystick();  break;
        case 's': test_serial_receiving();  break;
        case 'z': test_buzzer_playing();    break;
        case 't': test_oled_display(); break;
        case 'D': test_tft_display(); break;
    }
    serial_print_str("\nDone!\n");

    for (;;) {}
}