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