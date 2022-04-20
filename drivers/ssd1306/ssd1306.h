/* SSD1306 I2C display driver.
 * In this project the display is used as a decorative
 * TV in the living room of the miniature house.
 * If an enemy (ghost) posesses the TV, it thould start showing
 * white noise. Therefore we need only an initialization, data writing
 * and scrolling functionality.
 */

#ifndef _SSD1306_H
#define _SSD1306_H

#include <stdint.h>
#include <stdbool.h>

void ssd1306_init(void);

void ssd1306_set_cursor(uint8_t page, uint8_t column);

void ssd1306_begin_write(void);
void ssd1306_write_byte(uint8_t b);
void ssd1306_end_write(void);

void ssd1306_clear(void);

void ssd1306_display_off(void);
void ssd1306_display_on(void);
void ssd1306_set_inverse(bool inverse);

void ssd1306_start_scrolling(void);
void ssd1306_stop_scrolling(void);

#endif  // _SSD1306_H