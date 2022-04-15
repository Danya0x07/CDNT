#include "uart.h"
#include <avr/interrupt.h>

static char rx_buffer[0x40] = {0};  // 64 bytes buffer, index mask 0x3F
static volatile bool is_empty = true;
static volatile uint8_t w_idx = 0;
static uint8_t r_idx = 0;

void uart_init(void)
{
    // baudrate: 9600
    UBRR0H = (uint8_t)(103 >> 8);
    UBRR0L = (uint8_t)103;
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
    uart_enable();
}

void uart_send_byte(uint8_t b)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = b;
}

ISR(USART_RX_vect)
{
    rx_buffer[w_idx++] = UDR0;
    w_idx &= 0x3F;
    is_empty = false;
}

bool uart_rx_buffer_empty(void)
{
    return is_empty;
}

uint8_t uart_read_byte(void)
{
    if (is_empty)
        return 0;
    
    uint8_t b = rx_buffer[r_idx++];
    r_idx &= 0x3F;

    if (r_idx == w_idx) {
        is_empty = true;
    }

    return b;
}

uint8_t uart_peek_last(void)
{
    if (is_empty)
        return 0;

    uint8_t idx = (w_idx - 1) & 0x3F;
    return rx_buffer[idx];
}

uint8_t uart_peek_first(void)
{
    return is_empty ? 0 : rx_buffer[r_idx];
}

void uart_flush_rx_buffer(void)
{
    r_idx = w_idx;
    is_empty = true;
}
