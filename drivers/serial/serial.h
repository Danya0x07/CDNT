#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>
#include <stdbool.h>

void serial_send_char(char c);
void serial_send_str(const char *s);
void serial_send_dec(int16_t n);
void serial_send_hex(int16_t n);

bool serial_line_received(void);
void serial_read_line(char *buff);

#endif  // _SERIAL_H