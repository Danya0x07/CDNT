#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>
#include <stdbool.h>

void serial_print_char(char c);
void serial_print_str(const char *s);
void serial_print_dec(int16_t n);
void serial_print_hex(int16_t n);

bool serial_line_received(void);
uint8_t serial_read_line(char *buff);

#endif  // _SERIAL_H