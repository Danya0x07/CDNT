#include <graphics.h>
#include <avr/pgmspace.h>

#define DEFINE_IMG(name, w, h, ...)   \
static const PROGMEM uint8_t bm_##name[] = __VA_ARGS__; \
const struct gfx_image img_##name = { \
    .bitmap = bm_##name, \
    .width = w, \
    .height = h \
}

DEFINE_IMG(copyright, 6, 8, {0x3C, 0x42, 0xBD, 0xA5, 0x42, 0x3C});
DEFINE_IMG(arrowup, 5, 8, {0x40, 0x20, 0x10, 0x20, 0x40});
DEFINE_IMG(arrowdown, 5, 8, {0x01, 0x02, 0x04, 0x02, 0x01});
DEFINE_IMG(ghost, 24, 24, {
    0xC0, 0xE0, 0xF8, 0x3C, 0x3E, 0x3E, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x3E, 0x3C, 0xF8, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3F, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF, 0xF0, 0xC0, 0xC0, 0x80, 0x80, 0xC0, 0xE0, 0x70,
    0x00, 0x00, 0x07, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x0F, 0x07, 0x01, 0x00
});
DEFINE_IMG(lamp_poltergeist, 24, 24, {
    0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x60, 0x30, 0x98, 0x8C, 0x04, 0x84, 0x8C, 0x38, 0xE0, 0x00,
    0x0F, 0x0F, 0x0C, 0x0C, 0xFC, 0x0C, 0x6C, 0xEF, 0x4F, 0x40, 0x70, 0x1C, 0x07, 0x01, 0x00, 0x80, 0x81, 0xC1, 0x60, 0x21, 0x31, 0x18, 0x0F, 0x00,
    0x00, 0x38, 0x78, 0xF8, 0xFF, 0xF8, 0x78, 0x39, 0x03, 0x02, 0x06, 0x04, 0x04, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
});
DEFINE_IMG(cam_poltergeist, 24, 24, {
    0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x38, 0x0E, 0x02, 0x32, 0x33, 0x01, 0x01, 0x31, 0x31, 0x03, 0x82, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x18, 0x30, 0x60, 0x30, 0x10, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF, 0x3C, 0x66, 0xC3, 0x81, 0xFF, 0x00, 0x00
});
DEFINE_IMG(joystick, 17, 17, {
    0x00, 0x80, 0xC0, 0x00, 0xC0, 0x60, 0x34, 0x16, 0x77, 0x16, 0x34, 0x60, 0xC0, 0x00, 0xC0, 0x80, 0x00,
    0x01, 0x03, 0x07, 0x00, 0x07, 0x0D, 0x59, 0xD0, 0xDC, 0xD0, 0x59, 0x0D, 0x07, 0x00, 0x07, 0x03, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
});
DEFINE_IMG(flash, 18, 8, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x1B, 0x1B, 0x1B, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
DEFINE_IMG(autoflash, 18, 8, {0xFF, 0xFF, 0x1B, 0x1B, 0x1B, 0x03, 0xF0, 0x50, 0xF0, 0xE0, 0x80, 0xE0, 0x10, 0xF0, 0x10, 0x60, 0x90, 0x60});
DEFINE_IMG(noopt, 18, 8, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
DEFINE_IMG(pause, 18, 8, {0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x81, 0xBD, 0x81, 0x81, 0xBD, 0x81, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00});
DEFINE_IMG(ceiling, 18, 8, {0xFF, 0x81, 0x99, 0xA5, 0xA5, 0x99, 0x81, 0xFF, 0x00, 0x00, 0xFF, 0x81, 0x99, 0xA5, 0xA5, 0x99, 0x81, 0xFF});
DEFINE_IMG(floorlamp, 18, 8, {0x00, 0x08, 0x49, 0x22, 0x14, 0x00, 0x0F, 0xC9, 0xB9, 0xB9, 0xC9, 0x0F, 0x00, 0x14, 0x22, 0x49, 0x08, 0x00});
DEFINE_IMG(desklamp, 18, 8, {0x00, 0x08, 0x49, 0x22, 0x14, 0x00, 0x1C, 0xA2, 0xE1, 0xE1, 0xA2, 0x1C, 0x00, 0x14, 0x22, 0x49, 0x08, 0x00});
DEFINE_IMG(tv, 18, 8, {0x04, 0x02, 0x0C, 0x10, 0x00, 0xBF, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xBF, 0x00, 0x10, 0x0C, 0x02, 0x04});
DEFINE_IMG(closecam, 18, 8, {0x00, 0x00, 0x00, 0xFF, 0x81, 0x81, 0xC9, 0xA5, 0x93, 0x93, 0xA5, 0xC9, 0x81, 0x81, 0xFF, 0x00, 0x00, 0x00});