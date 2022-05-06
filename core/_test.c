#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>

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

#include <graphics.h>
#include <music.h>

#include <init.h>
#include <_test.h>

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

    st7735_set_window(10, 10, 100, 100);

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
}

void test_graphics(void)
{
    static const PROGMEM uint8_t bitmap[8] = {0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0};
    struct gfx_image img = {
        .bitmap = bitmap,
        .width = 8,
        .height = 8
    };
    
    serial_print_str("Testing TFT display!\n");

    gfx_clear();
    ms_wait(2000);
    gfx_draw_image(80, 110, &img);
    gfx_draw_rect(15, 30, 6, 3);
    gfx_draw_frame(30, 15, 20, 15, 5);
    gfx_print_txt(80, 2, "the");

    gfx_set_color(GFX_COLOR_RED, GFX_COLOR_BLUE);
    gfx_set_scale(GFX_SCALE_X3);
    gfx_print_txt(10, 40, test_msg1);

    gfx_set_color(GFX_COLOR_BLACK, GFX_COLOR_YELLOW);
    gfx_set_scale(GFX_SCALE_X2);
    gfx_print_txt(40, 80, test_msg2);
}

void test_music(void)
{
    char buffer[40];
    char *pch;
    uint16_t notes[5][2] = {{400, 800}, {900, 600}, {400, 800}, {0, 1000}, {640, 200}};
    uint8_t k;

    struct music_track track = {&notes[0], 5, false};
    
    serial_print_str("Testing music!\n");

    music_play(&track);
    for (uint32_t now = ms_passed(); ms_passed() - now < 600;)
        music_update();
    music_stop();
    ms_wait(500);
    music_play(&track);
    while (music_playing())
        music_update();

    for (;;) {
        serial_print_str("\nEnter some notes and durations: ");
        while (!serial_line_received())
            ms_wait(100);
        serial_read_line(buffer);
        k = 0;
        pch = strtok(buffer, " ");
        while (pch && k < 5) {
            notes[k][0] = atoi(pch);
            pch = strtok(NULL, " ");
            if (!pch)
                return;
                
            notes[k][1] = atoi(pch);
            pch = strtok(NULL, " ");
            if (!notes[k][1])
                return;

            serial_print_dec(notes[k][0]);
            serial_print_char(' ');
            serial_print_dec(notes[k][1]);
            serial_print_char(' ');
            k++;
        }
        track.len = k;
        serial_print_str("Track len: ");
        serial_print_dec(k);
        music_play(&track);
        while (music_playing())
            music_update();
    }
}

int main(void)
{
    init_hal();
    init_drivers();

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
        case 'G': test_graphics(); break;
        case 'm': test_music(); break;
    }
    serial_print_str("\nDone!\n");

    for (;;) {}
}