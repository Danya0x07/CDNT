#include "graphics.h"
#include <st7735.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>

static const PROGMEM uint8_t ascii_charset[][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00},  /* 20 SPACE */
    {0x00, 0x00, 0x5f, 0x00, 0x00},  /* 21 ! */
    {0x00, 0x07, 0x00, 0x07, 0x00},  /* 22 " */
    {0x14, 0x7f, 0x14, 0x7f, 0x14},  /* 23 # */
    {0x24, 0x2a, 0x7f, 0x2a, 0x12},  /* 24 $ */
    {0x23, 0x13, 0x08, 0x64, 0x62},  /* 25 % */
    {0x36, 0x49, 0x55, 0x22, 0x50},  /* 26 & */
    {0x00, 0x05, 0x03, 0x00, 0x00},  /* 27 ' */
    {0x00, 0x1c, 0x22, 0x41, 0x00},  /* 28 ( */
    {0x00, 0x41, 0x22, 0x1c, 0x00},  /* 29 ) */
    {0x14, 0x08, 0x3e, 0x08, 0x14},  /* 2a * */
    {0x08, 0x08, 0x3e, 0x08, 0x08},  /* 2b + */
    {0x00, 0x50, 0x30, 0x00, 0x00},  /* 2c , */
    {0x08, 0x08, 0x08, 0x08, 0x08},  /* 2d - */
    {0x00, 0x60, 0x60, 0x00, 0x00},  /* 2e . */
    {0x20, 0x10, 0x08, 0x04, 0x02},  /* 2f / */
    {0x3e, 0x51, 0x49, 0x45, 0x3e},  /* 30 0 */
    {0x00, 0x42, 0x7f, 0x40, 0x00},  /* 31 1 */
    {0x42, 0x61, 0x51, 0x49, 0x46},  /* 32 2 */
    {0x21, 0x41, 0x45, 0x4b, 0x31},  /* 33 3 */
    {0x18, 0x14, 0x12, 0x7f, 0x10},  /* 34 4 */
    {0x27, 0x45, 0x45, 0x45, 0x39},  /* 35 5 */
    {0x3c, 0x4a, 0x49, 0x49, 0x30},  /* 36 6 */
    {0x01, 0x71, 0x09, 0x05, 0x03},  /* 37 7 */
    {0x36, 0x49, 0x49, 0x49, 0x36},  /* 38 8 */
    {0x06, 0x49, 0x49, 0x29, 0x1e},  /* 39 9 */
    {0x00, 0x36, 0x36, 0x00, 0x00},  /* 3a : */
    {0x00, 0x56, 0x36, 0x00, 0x00},  /* 3b ; */
    {0x08, 0x14, 0x22, 0x41, 0x00},  /* 3c < */
    {0x14, 0x14, 0x14, 0x14, 0x14},  /* 3d = */
    {0x00, 0x41, 0x22, 0x14, 0x08},  /* 3e > */
    {0x02, 0x01, 0x51, 0x09, 0x06},  /* 3f ? */
    {0x32, 0x49, 0x79, 0x41, 0x3e},  /* 40 @ */
    {0x7e, 0x11, 0x11, 0x11, 0x7e},  /* 41 A */
    {0x7f, 0x49, 0x49, 0x49, 0x36},  /* 42 B */
    {0x3e, 0x41, 0x41, 0x41, 0x22},  /* 43 C */
    {0x7f, 0x41, 0x41, 0x22, 0x1c},  /* 44 D */
    {0x7f, 0x49, 0x49, 0x49, 0x41},  /* 45 E */
    {0x7f, 0x09, 0x09, 0x09, 0x01},  /* 46 F */
    {0x3e, 0x41, 0x49, 0x49, 0x7a},  /* 47 G */
    {0x7f, 0x08, 0x08, 0x08, 0x7f},  /* 48 H */
    {0x00, 0x41, 0x7f, 0x41, 0x00},  /* 49 I */
    {0x20, 0x40, 0x41, 0x3f, 0x01},  /* 4a J */
    {0x7f, 0x08, 0x14, 0x22, 0x41},  /* 4b K */
    {0x7f, 0x40, 0x40, 0x40, 0x40},  /* 4c L */
    {0x7f, 0x02, 0x0c, 0x02, 0x7f},  /* 4d M */
    {0x7f, 0x04, 0x08, 0x10, 0x7f},  /* 4e N */
    {0x3e, 0x41, 0x41, 0x41, 0x3e},  /* 4f O */
    {0x7f, 0x09, 0x09, 0x09, 0x06},  /* 50 P */
    {0x3e, 0x41, 0x51, 0x21, 0x5e},  /* 51 Q */
    {0x7f, 0x09, 0x19, 0x29, 0x46},  /* 52 R */
    {0x46, 0x49, 0x49, 0x49, 0x31},  /* 53 S */
    {0x01, 0x01, 0x7f, 0x01, 0x01},  /* 54 T */
    {0x3f, 0x40, 0x40, 0x40, 0x3f},  /* 55 U */
    {0x1f, 0x20, 0x40, 0x20, 0x1f},  /* 56 V */
    {0x3f, 0x40, 0x38, 0x40, 0x3f},  /* 57 W */
    {0x63, 0x14, 0x08, 0x14, 0x63},  /* 58 X */
    {0x07, 0x08, 0x70, 0x08, 0x07},  /* 59 Y */
    {0x61, 0x51, 0x49, 0x45, 0x43},  /* 5a Z */
    {0x00, 0x7f, 0x41, 0x41, 0x00},  /* 5b [ */
    {0x02, 0x04, 0x08, 0x10, 0x20},  /* 5c \ */
    {0x00, 0x41, 0x41, 0x7f, 0x00},  /* 5d ] */
    {0x04, 0x02, 0x01, 0x02, 0x04},  /* 5e ^ */
    {0x40, 0x40, 0x40, 0x40, 0x40},  /* 5f _ */
    {0x00, 0x01, 0x02, 0x04, 0x00},  /* 60 ` */
    {0x20, 0x54, 0x54, 0x54, 0x78},  /* 61 a */
    {0x7f, 0x48, 0x44, 0x44, 0x38},  /* 62 b */
    {0x38, 0x44, 0x44, 0x44, 0x20},  /* 63 c */
    {0x38, 0x44, 0x44, 0x48, 0x7f},  /* 64 d */
    {0x38, 0x54, 0x54, 0x54, 0x18},  /* 65 e */
    {0x08, 0x7e, 0x09, 0x01, 0x02},  /* 66 f */
    {0x0c, 0x52, 0x52, 0x52, 0x3e},  /* 67 g */
    {0x7f, 0x08, 0x04, 0x04, 0x78},  /* 68 h */
    {0x00, 0x44, 0x7d, 0x40, 0x00},  /* 69 i */
    {0x20, 0x40, 0x44, 0x3d, 0x00},  /* 6a j */
    {0x7f, 0x10, 0x28, 0x44, 0x00},  /* 6b k */
    {0x00, 0x41, 0x7f, 0x40, 0x00},  /* 6c l */
    {0x7c, 0x04, 0x18, 0x04, 0x78},  /* 6d m */
    {0x7c, 0x08, 0x04, 0x04, 0x78},  /* 6e n */
    {0x38, 0x44, 0x44, 0x44, 0x38},  /* 6f o */
    {0x7c, 0x14, 0x14, 0x14, 0x08},  /* 70 p */
    {0x08, 0x14, 0x14, 0x18, 0x7c},  /* 71 q */
    {0x7c, 0x08, 0x04, 0x04, 0x08},  /* 72 r */
    {0x48, 0x54, 0x54, 0x54, 0x20},  /* 73 s */
    {0x04, 0x3f, 0x44, 0x40, 0x20},  /* 74 t */
    {0x3c, 0x40, 0x40, 0x20, 0x7c},  /* 75 u */
    {0x1c, 0x20, 0x40, 0x20, 0x1c},  /* 76 v */
    {0x3c, 0x40, 0x30, 0x40, 0x3c},  /* 77 w */
    {0x44, 0x28, 0x10, 0x28, 0x44},  /* 78 x */
    {0x0c, 0x50, 0x50, 0x50, 0x3c},  /* 79 y */
    {0x44, 0x64, 0x54, 0x4c, 0x44},  /* 7a z */
    {0x00, 0x08, 0x36, 0x41, 0x00},  /* 7b { */
    {0x00, 0x00, 0x7f, 0x00, 0x00},  /* 7c | */
    {0x00, 0x41, 0x36, 0x08, 0x00},  /* 7d } */
    {0x10, 0x08, 0x08, 0x10, 0x08}   /* 7e ~ */
};

static const PROGMEM uint8_t russian_charset[][5] = {
    {0x7e, 0x11, 0x11, 0x11, 0x7e},  // 80 А
    {0x7f, 0x49, 0x49, 0x49, 0x33},  // 81 Б
    {0x7f, 0x49, 0x49, 0x49, 0x36},  // 82 В
    {0x7f, 0x01, 0x01, 0x01, 0x03},  // 83 Г
    {0xe0, 0x51, 0x4f, 0x41, 0xff},  // 84 Д
    {0x7f, 0x49, 0x49, 0x49, 0x41},  // 85 Е
    {0x77, 0x08, 0x7f, 0x08, 0x77},  // 86 Ж
    {0x41, 0x49, 0x49, 0x49, 0x36},  // 87 З
    {0x7f, 0x10, 0x08, 0x04, 0x7f},  // 88 И
    {0x7c, 0x21, 0x12, 0x09, 0x7c},  // 89 Й
    {0x7f, 0x08, 0x14, 0x22, 0x41},  // 8A К
    {0x20, 0x41, 0x3f, 0x01, 0x7f},  // 8B Л
    {0x7f, 0x02, 0x0c, 0x02, 0x7f},  // 8C М
    {0x7f, 0x08, 0x08, 0x08, 0x7f},  // 8D Н
    {0x3e, 0x41, 0x41, 0x41, 0x3e},  // 8E О
    {0x7f, 0x01, 0x01, 0x01, 0x7f},  // 8F П
    {0x7f, 0x09, 0x09, 0x09, 0x06},  // 90 Р
    {0x3e, 0x41, 0x41, 0x41, 0x22},  // 91 С
    {0x01, 0x01, 0x7f, 0x01, 0x01},  // 92 Т
    {0x47, 0x28, 0x10, 0x08, 0x07},  // 93 У
    {0x1c, 0x22, 0x7f, 0x22, 0x1c},  // 94 Ф
    {0x63, 0x14, 0x08, 0x14, 0x63},  // 95 Х
    {0x7f, 0x40, 0x40, 0x40, 0xff},  // 96 Ц
    {0x07, 0x08, 0x08, 0x08, 0x7f},  // 97 Ч
    {0x7f, 0x40, 0x7f, 0x40, 0x7f},  // 98 Ш
    {0x7f, 0x40, 0x7f, 0x40, 0xff},  // 99 Щ
    {0x01, 0x7f, 0x48, 0x48, 0x30},  // 9A Ъ
    {0x7f, 0x48, 0x30, 0x00, 0x7f},  // 9B Ы
    {0x00, 0x7f, 0x48, 0x48, 0x30},  // 9C Э
    {0x22, 0x41, 0x49, 0x49, 0x3e},  // 9D Ь
    {0x7f, 0x08, 0x3e, 0x41, 0x3e},  // 9E Ю
    {0x46, 0x29, 0x19, 0x09, 0x7f},  // 9F Я
    {0x20, 0x54, 0x54, 0x54, 0x78},  // A0 а
    {0x3c, 0x4a, 0x4a, 0x49, 0x31},  // A1 б
    {0x7c, 0x54, 0x54, 0x28, 0x00},  // A2 в
    {0x7c, 0x04, 0x04, 0x04, 0x0c},  // A3 г
    {0xe0, 0x54, 0x4c, 0x44, 0xfc},  // A4 д
    {0x38, 0x54, 0x54, 0x54, 0x18},  // A5 е
    {0x6c, 0x10, 0x7c, 0x10, 0x6c},  // A6 ж
    {0x44, 0x44, 0x54, 0x54, 0x28},  // A7 з
    {0x7c, 0x20, 0x10, 0x08, 0x7c},  // A8 и
    {0x7c, 0x41, 0x22, 0x11, 0x7c},  // A9 й
    {0x7c, 0x10, 0x28, 0x44, 0x00},  // AA к
    {0x20, 0x44, 0x3c, 0x04, 0x7c},  // AB л
    {0x7c, 0x08, 0x10, 0x08, 0x7c},  // AC м
    {0x7c, 0x10, 0x10, 0x10, 0x7c},  // AD н
    {0x38, 0x44, 0x44, 0x44, 0x38},  // AE о
    {0x7c, 0x04, 0x04, 0x04, 0x7c},  // AF п
    {0x7C, 0x14, 0x14, 0x14, 0x08},  // E0 р
    {0x38, 0x44, 0x44, 0x44, 0x20},  // E1 с
    {0x04, 0x04, 0x7c, 0x04, 0x04},  // E2 т
    {0x0C, 0x50, 0x50, 0x50, 0x3C},  // E3 у
    {0x30, 0x48, 0xfc, 0x48, 0x30},  // E4 ф
    {0x44, 0x28, 0x10, 0x28, 0x44},  // E5 х
    {0x7c, 0x40, 0x40, 0x40, 0xfc},  // E6 ц
    {0x0c, 0x10, 0x10, 0x10, 0x7c},  // E7 ч
    {0x7c, 0x40, 0x7c, 0x40, 0x7c},  // E8 ш
    {0x7c, 0x40, 0x7c, 0x40, 0xfc},  // E9 щ
    {0x04, 0x7c, 0x50, 0x50, 0x20},  // EA ъ
    {0x7c, 0x50, 0x50, 0x20, 0x7c},  // EB ы
    {0x7c, 0x50, 0x50, 0x20, 0x00},  // EC ь
    {0x28, 0x44, 0x54, 0x54, 0x38},  // ED э
    {0x7c, 0x10, 0x38, 0x44, 0x38},  // EE ю
    {0x08, 0x54, 0x34, 0x14, 0x7c},  // EF я
    {0x7C, 0x55, 0x54, 0x55, 0x44},  // F0 Ё
    {0x38, 0x55, 0x54, 0x55, 0x18}   // F1 ё
};

#define CHAR_BITMAP_WIDTH   5
#define CHAR_BITMAP_HEIGHT  7
#define CHAR_PLACE_WIDTH    (CHAR_BITMAP_WIDTH + 1)
#define CHAR_PLACE_HEIGHT   (CHAR_BITMAP_HEIGHT + 1)


static struct {
    enum gfx_color foreground;
    enum gfx_color background;
    enum gfx_scale_factor scale;
} settings = {
    .foreground = GFX_COLOR_WHITE,
    .background = GFX_COLOR_BLACK,
    .scale = GFX_SCALE_X1,
};


/* Get the bitmap of a character.
 *
 * The idea is to return the addresses of bitmap images of characters from
 * different font tables depending on the selected language.
 */
static const uint8_t *get_character_bitmap(uint8_t c)
{
    const uint8_t *bitmap = (const uint8_t *)&ascii_charset[c - 0x20];

    if (c >= 0x80) {  // non-ASCII character
        if (c < 0xE0)
            c -= 0x80;
        else
            c -= 0xB0;
        bitmap = (const uint8_t *)&russian_charset[c];
    }

    return bitmap;
}

void gfx_clear_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
    st7735_set_window(x, y, w, h);
    st7735_start_ram_write();
    for (uint16_t i = 0; i < w * h; i++)
        st7735_write_pixel(settings.background);
}

void gfx_clear(void)
{
    gfx_clear_rect(0, 0, ST7735_WIDTH, ST7735_HEIGHT);
}

void gfx_set_color(enum gfx_color fg, enum gfx_color bg)
{
    settings.foreground = fg;
    settings.background = bg;
}

void gfx_set_scale(enum gfx_scale_factor scale)
{
    settings.scale = scale;
}

void gfx_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
    st7735_set_window(x, y, w, h);
    st7735_start_ram_write();
    for (uint16_t i = 0; i < w * h; i++)
        st7735_write_pixel(settings.foreground);
}

void gfx_draw_frame(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t th)
{
    gfx_draw_rect(x, y, w, th);
    gfx_draw_rect(x, y + th, th, h - th);
    gfx_draw_rect(x + w - th, y + th, th, h - th);
    gfx_draw_rect(x, y + h - th, w, th);
}

void gfx_draw_image(uint8_t x, uint8_t y, const struct gfx_image *img)
{
    uint8_t total_w = img->width * settings.scale;
    uint8_t total_h = img->height * settings.scale;
    uint8_t idx, byte, bit;

    st7735_set_window(x, y, total_w, total_h);
    st7735_start_ram_write();
    for (uint8_t v_px = 0; v_px < img->height; v_px++) {
        for (uint8_t v_scale = 0; v_scale < settings.scale; v_scale++) {
            for (uint8_t h_px = 0; h_px < img->width; h_px++) {
                for (uint8_t h_scale = 0; h_scale < settings.scale; h_scale++) {
                    idx = (v_px >> 3) * img->width + h_px;
                    byte = pgm_read_byte(&img->bitmap[idx]);
                    bit = byte & (1 << (v_px & 0x07));
                    st7735_write_pixel(bit ? settings.foreground : settings.background);
                }
            }
        }
    }
}

void gfx_print_ch(uint8_t x, uint8_t y, char ch)
{
    struct gfx_image img = {
        .bitmap = get_character_bitmap(ch),
        .width = CHAR_BITMAP_WIDTH,
        .height = CHAR_PLACE_HEIGHT  // Let image drawing algorithm draw vertical spacing.
    };
    gfx_draw_image(x, y, &img);

    // Draw a little spacing between characters.
    x += CHAR_BITMAP_WIDTH * settings.scale;
    st7735_set_window(x, y, 1 * settings.scale, CHAR_PLACE_HEIGHT * settings.scale);
    st7735_start_ram_write();
    for (uint8_t i = 0; i < CHAR_PLACE_HEIGHT * settings.scale * settings.scale; i++)
        st7735_write_pixel(settings.background);
}

void gfx_print_txt(uint8_t x, uint8_t y, const char *txt)
{
    char c;
    
    while (y <= ST7735_MAX_X - CHAR_PLACE_HEIGHT * settings.scale) {
        while (x <= ST7735_MAX_X - CHAR_PLACE_WIDTH * settings.scale) {
            c = *txt++;
            if (c == '\n')
                break;
            if (c == '\0')
                return;
            gfx_print_ch(x, y, c);
            x += CHAR_PLACE_WIDTH * settings.scale;
        }
        y += CHAR_PLACE_HEIGHT * settings.scale;
        x = 0;
    }
}

void gfx_print_txt_f(uint8_t x, uint8_t y, const char *txt)
{
    char c;
    
    while (y <= ST7735_MAX_X - CHAR_PLACE_HEIGHT * settings.scale) {
        while (x <= ST7735_MAX_X - CHAR_PLACE_WIDTH * settings.scale) {
            c = pgm_read_byte(txt++);
            if (c == '\n')
                break;
            if (c == '\0')
                return;
            gfx_print_ch(x, y, c);
            x += CHAR_PLACE_WIDTH * settings.scale;
        }
        y += CHAR_PLACE_HEIGHT * settings.scale;
        x = 0;
    }
}

uint8_t gfx_print_dec(uint8_t x, uint8_t y, int16_t n)
{
    static char buff[16];
    snprintf(buff, 16, "%d", n);
    uint8_t next_x = x + strlen(buff) * CHAR_PLACE_WIDTH * settings.scale;
    gfx_print_txt(x, y, buff);
    return next_x;
}
