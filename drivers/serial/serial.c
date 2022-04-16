#include "serial.h"
#include <stdlib.h>
#include <hal/uart.h>

static char strbuffer[17];

void serial_send_char(char c)
{
    uart_send_byte(c);
}

void serial_send_str(const char *s)
{
    while (*s)
        uart_send_byte(*s++);
}

void serial_send_dec(int16_t n)
{
    serial_send_str(itoa(n, strbuffer, 10));
}

void serial_send_hex(int16_t n)
{
    serial_send_str(itoa(n, strbuffer, 16));
}


bool serial_line_received(void)
{
    return uart_peek_last() == '\n';
}

uint8_t serial_read_line(char *buff)
{
    if (!serial_line_received()) {
        buff = NULL;
        return 0;
    }

    uint8_t len = 0;
    char c = uart_read_byte();
    while (c != '\n') {
        *buff++ = c;
        len++;
        c = uart_read_byte();
    }
    *buff = '\0';
    
    return len;
}
