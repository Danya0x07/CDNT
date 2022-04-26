#ifndef _ST7735_H
#define _ST7735_H

#include <stdint.h>
#include <stdbool.h>

// Max coordinate values
#define ST7735_MAX_X   159
#define ST7735_MAX_Y   127

enum st7735_gamma_curve {
    ST7735_GAMMA_2_2 = 1,
    ST7735_GAMMA_1_8 = 2,
    ST7735_GAMMA_2_5 = 4,
    ST7735_GAMMA_1_0 = 8
};

void st7735_init(void);
void st7735_set_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void st7735_start_ram_write(void);
void st7735_write_pixel(uint16_t color);
void st7735_set_gamma_curve(enum st7735_gamma_curve curve);
void st7735_display_off(void);
void st7735_display_on(void);
void st7735_set_inverse(bool inverse);

#endif  // _ST7735_H