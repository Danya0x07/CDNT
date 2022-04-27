#ifndef _ST7735_H
#define _ST7735_H

#include <stdint.h>
#include <stdbool.h>

#define ST7735_WIDTH    160
#define ST7735_HEIGHT   128
#define ST7735_MAX_X   (ST7735_WIDTH - 1)
#define ST7735_MAX_Y   (ST7735_HEIGHT - 1)

void st7735_init(void);
void st7735_set_window(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void st7735_start_ram_write(void);
void st7735_write_pixel(uint16_t color);
void st7735_display_off(void);
void st7735_display_on(void);
void st7735_set_inverse(bool inverse);

#endif  // _ST7735_H