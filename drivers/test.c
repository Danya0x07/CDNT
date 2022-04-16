#include <avr/interrupt.h>

#include <hal/adc.h>
#include <hal/spi.h>
#include <hal/timers.h>
#include <hal/uart.h>

#include <joystick.h>
#include <serial.h>
#include <shiftreg.h>

void system_init(void)
{
    adc_init();
    spi_init();
    timers_init();
    uart_init();
    sei();

    shiftreg_init();
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
    }

    for (;;) {}
}