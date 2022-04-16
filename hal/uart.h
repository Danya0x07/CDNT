#ifndef _HAL_UART_H
#define _HAL_UART_H

#include <avr/io.h>
#include <stdbool.h>

/* Initialize and enable UART on 9600 baudrate. */
void uart_init(void);

/* Macro to control UART ability to receive and send data. */
#define uart_enable()   (UCSR0B = _BV(TXEN0) | _BV(RXEN0) | _BV(RXCIE0))
#define uart_disable()  (UCSR0B = 0)

void uart_send_byte(uint8_t b);

bool uart_rx_buffer_empty(void);

/* Returns 0 if buffer empty. */
uint8_t uart_read_byte(void);
uint8_t uart_peek_last(void);
uint8_t uart_peek_first(void);

void uart_flush_rx_buffer(void);

#endif  // _HAL_UART_H