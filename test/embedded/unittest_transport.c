#include <unity_config.h>
#include <hal/uart.h>

void unittest_uart_begin()
{
    uart_init();
}

void unittest_uart_putchar(char c)
{
    uart_send_byte(c);
}

void unittest_uart_flush()
{
    uart_flush_rx_buffer();
}

void unittest_uart_end()
{
    uart_disable();
}