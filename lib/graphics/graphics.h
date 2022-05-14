/** Tiny graphics library for project needs.
 * Working with TFT display. No more flexibility than needed.
 */

#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>

enum gfx_color {
    GFX_COLOR_BLACK =    0x0000,
    GFX_COLOR_RED =      0xF800,
    GFX_COLOR_GREEN =    0x07E0,
    GFX_COLOR_BLUE =     0x001F,
    GFX_COLOR_CYAN =     0x07FF,
    GFX_COLOR_MAGENTA =  0xF81F,
    GFX_COLOR_YELLOW =   0xFFE0, 
    GFX_COLOR_WHITE =    0xFFFF 
};

enum gfx_scale_factor {
    GFX_SCALE_X1 = 1,
    GFX_SCALE_X2,
    GFX_SCALE_X3
};

/* Image structure for drawing on the screen.
 * Bitmap field expects standart format as in monochrome display libraries used.
 * Width and height are in pixels. For example, if image is 8x10 px then it's size
 * will be 16 bytes, and first 8 bytes will form the "upper" part of the image and
 * from second 8 bytes only 2 bits will have meaning. */
struct gfx_image {
    const uint8_t *bitmap;
    uint8_t width;
    uint8_t height;
};

// Fill screen with background color.
void gfx_clear(void);
void gfx_clear_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void gfx_set_color(enum gfx_color fg, enum gfx_color bg);
void gfx_set_scale(enum gfx_scale_factor scale);

// Scaling-independent functions.
void gfx_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void gfx_draw_frame(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t th);

// Scaling-dependent functions.
void gfx_draw_image(uint8_t x, uint8_t y, const struct gfx_image *img);
void gfx_print_ch(uint8_t x, uint8_t y, char ch);
void gfx_print_txt(uint8_t x, uint8_t y, const char *txt);
void gfx_print_txt_f(uint8_t x, uint8_t y, const char *txt);
uint8_t gfx_print_dec(uint8_t x, uint8_t y, int16_t n);

#endif // _GRAPHICS_H