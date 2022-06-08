#include <house.h>
#include <shiftreg.h>
#include <ssd1306.h>
#include "shifts.h"

#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>

#define SHIFT_NA    0xFF

static const PROGMEM uint8_t ceiling_lights[] = {
    SHIFT_R1_C,
    SHIFT_R2_C,
    SHIFT_R3_C,
    SHIFT_R4_C,
    SHIFT_R5_C,
    SHIFT_R6_C,
    SHIFT_R7_C,
};

static const PROGMEM uint8_t room_lights[] = {
    SHIFT_R3_L1,
    SHIFT_R4_L1,
    SHIFT_R6_L1,
    SHIFT_R6_L2,
    SHIFT_R7_L1,
    SHIFT_R7_L2,
};

static const PROGMEM uint8_t camera_lights[][2] = {
    {SHIFT_R1_W, SHIFT_R1_UV},
    {SHIFT_R2_W, SHIFT_R2_UV},
    {SHIFT_R3_W, SHIFT_R3_UV},
    {SHIFT_R4_W, SHIFT_R4_UV},
    {SHIFT_R5_W, SHIFT_R5_UV},
    {SHIFT_R6_W, SHIFT_R6_UV},
    {SHIFT_R7_W, SHIFT_R7_UV},
    {SHIFT_RP_W, SHIFT_NA} // Camera in the player's room doesn't have UV mode
};

static const PROGMEM uint8_t flash_lights[][2] = {
    {SHIFT_FL_W, SHIFT_FL_UV},
    {SHIFT_FR_W, SHIFT_FR_UV}
};

static const PROGMEM uint8_t drawings[][3] = {
    {SHIFT_R1_D1_R, SHIFT_R1_D1_G, SHIFT_R1_D1_B},
    {SHIFT_R1_D2_R, SHIFT_R1_D2_G, SHIFT_R1_D2_B},
    {SHIFT_R2_D1_R, SHIFT_R2_D1_G, SHIFT_R2_D1_B},
    {SHIFT_R2_D2_R, SHIFT_R2_D2_G, SHIFT_R2_D2_B},
    {SHIFT_R3_D1_R, SHIFT_R3_D1_G, SHIFT_R3_D1_B},
    {SHIFT_R3_D2_R, SHIFT_R3_D2_G, SHIFT_R3_D2_B},
    {SHIFT_R4_D1_R, SHIFT_R4_D1_G, SHIFT_R4_D1_B},
    {SHIFT_R4_D2_R, SHIFT_R4_D2_G, SHIFT_R4_D2_B},
    {SHIFT_R5_D1_R, SHIFT_R5_D1_G, SHIFT_R5_D1_B},
    {SHIFT_R6_D1_R, SHIFT_R6_D1_G, SHIFT_R6_D1_B},
    {SHIFT_R6_D2_R, SHIFT_R6_D2_G, SHIFT_R6_D2_B},
    {SHIFT_R7_D1_R, SHIFT_R7_D1_G, SHIFT_R7_D1_B},
    {SHIFT_R7_D2_R, SHIFT_R7_D2_G, SHIFT_R7_D2_B},
    {SHIFT_RP_D1_R, SHIFT_RP_D1_G, SHIFT_RP_D1_B},
    {SHIFT_RP_D2_R, SHIFT_RP_D2_G, SHIFT_RP_D2_B},
    {SHIFT_RP_D3_R, SHIFT_RP_D3_G, SHIFT_RP_D3_B}
};

#define BM(shift) (1 << ((SHIFT_##shift) & 7))

static const PROGMEM uint8_t lamps_memmasks[8][4] = {
    { // Room 1
/* 0..7   */ 0,
/* 8..15  */ BM(R1_W) | BM(R1_UV),
/* 16..23 */ 0,
/* 24..31 */ BM(R1_C)
    },
    { // Room 2
/* 0..7   */ 0,
/* 8..15  */ 0,
/* 16..23 */ BM(R2_W) | BM(R2_UV),
/* 24..31 */ BM(R2_C)
    },
    { // Room 3
/* 0..7   */ BM(R3_UV),
/* 8..15  */ BM(R3_W),
/* 16..23 */ 0,
/* 24..31 */ BM(R3_C) | BM(R3_L1)
    },
    { // Room 4
/* 0..7   */ BM(R4_W) | BM(R4_UV),
/* 8..15  */ 0,
/* 16..23 */ BM(R4_L1),
/* 24..31 */ BM(R4_C)
    },
    { // Room 5
/* 0..7   */ 0,
/* 8..15  */ BM(R5_W) | BM(R5_UV),
/* 16..23 */ 0,
/* 24..31 */ BM(R5_C)
    },
    { // Room 6
/* 0..7   */ 0,
/* 8..15  */ BM(R6_W) | BM(R6_UV),
/* 16..23 */ BM(R6_L1) | BM(R6_L2),
/* 24..31 */ BM(R6_C)
    },
    { // Room 7
/* 0..7   */ 0,
/* 8..15  */ BM(R7_UV),
/* 16..23 */ BM(R7_L1) | BM(R7_L2) | BM(R7_W),
/* 24..31 */ BM(R7_C)
    },
    { // Player's room
/* 0..7   */ BM(RP_W) | BM(FR_UV) | BM(FR_W) | BM(FL_W) | BM(FL_UV),
/* 8..15  */ 0,
/* 16..23 */ 0,
/* 24..31 */ 0
    },
};

static const PROGMEM uint8_t drawings_memmasks[8][6] = {
    { // Room 1
/* 0..7   */ BM(R1_D2_R) | BM(R1_D2_G) | BM(R1_D1_B) | BM(R1_D1_R) | BM(R1_D1_G),
/* 8..15  */ BM(R1_D2_B),
/* 16..23 */ 0,
/* 24..31 */ 0,
/* 32..39 */ 0,
/* 40..47 */ 0
    },
    { // Room 2
/* 0..7   */ 0,
/* 8..15  */ BM(R2_D1_B) | BM(R2_D1_R) | BM(R2_D1_G),
/* 16..23 */ BM(R2_D2_B) | BM(R2_D2_R) | BM(R2_D2_G),
/* 24..31 */ 0,
/* 32..39 */ 0,
/* 40..47 */ 0
    },
    { // Room 3
/* 0..7   */ 0,
/* 8..15  */ 0,
/* 16..23 */ 0,
/* 24..31 */ 0,
/* 32..39 */ 0,
/* 40..47 */ BM(R3_D1_B) | BM(R3_D1_R) | BM(R3_D1_G) | BM(R3_D2_B) | BM(R3_D2_R) | BM(R3_D2_G)
    },
    { // Room 4
/* 0..7   */ 0,
/* 8..15  */ 0,
/* 16..23 */ 0,
/* 24..31 */ 0,
/* 32..39 */ BM(R4_D1_G) | BM(R4_D2_B) | BM(R4_D2_R) | BM(R4_D2_G),
/* 40..47 */ BM(R4_D1_B) | BM(R4_D1_R)
    },
    { // Room 5
/* 0..7   */ 0,
/* 8..15  */ 0,
/* 16..23 */ 0,
/* 24..31 */ BM(R5_D1_R) | BM(R5_D1_G),
/* 32..39 */ BM(R5_D1_B),
/* 40..47 */ 0
    },
    { // Room 6
/* 0..7   */ 0,
/* 8..15  */ 0,
/* 16..23 */ 0,
/* 24..31 */ BM(R6_D2_B) | BM(R6_D2_R) | BM(R6_D2_G),
/* 32..39 */ BM(R6_D1_B) | BM(R6_D1_R) | BM(R6_D1_G),
/* 40..47 */ 0
    },
    { // Room 7
/* 0..7   */ 0,
/* 8..15  */ BM(R7_D1_G),
/* 16..23 */ BM(R7_D1_B) | BM(R7_D1_R),
/* 24..31 */ BM(R7_D2_B) | BM(R7_D2_R) | BM(R7_D2_G),
/* 32..39 */ 0,
/* 40..47 */ 0
    },
    { // Player's room
/* 0..7   */ BM(RP_D1_B) | BM(RP_D1_R) | BM(RP_D1_G),
/* 8..15  */ BM(RP_D2_B) | BM(RP_D2_R) | BM(RP_D2_G),
/* 16..23 */ BM(RP_D3_B) | BM(RP_D3_R) | BM(RP_D3_G),
/* 24..31 */ 0,
/* 32..39 */ 0,
/* 40..47 */ 0
    },
};

static uint8_t lamps_memblock[4] = {0};
static uint8_t drawings_memblock[6] = {0};
static uint8_t current_mask = 0xFF;
static bool tv_status = OFF;

static void set_bit(uint8_t *memblock, uint8_t shift, bool status)
{
    uint8_t idx = shift >> 3;

    if (shift == SHIFT_NA)
        return;
    
    shift &= 7;
    if (status) {
        memblock[idx] |= 1 << shift;
    } else {
        memblock[idx] &= ~(1 << shift);
    }
}

void ceiling_light_set(enum ceiling id, bool status)
{
    uint8_t shift = pgm_read_byte(&ceiling_lights[id]);
    set_bit(lamps_memblock, shift, status);
}

void lamp_light_set(enum room_lamp id, bool status)
{
    uint8_t shift = pgm_read_byte(&room_lights[id]);
    set_bit(lamps_memblock, shift, status);
}

void camera_light_set(enum camera_no id, enum camera_mode mode)
{
    uint8_t shift_w = pgm_read_byte(&camera_lights[id][0]);
    uint8_t shift_uv = pgm_read_byte(&camera_lights[id][1]);

    set_bit(lamps_memblock, shift_w, !!(mode & 0b01));
    set_bit(lamps_memblock, shift_uv, !!(mode & 0b10));
}

void flash_light_set(enum flash id, enum flash_mode mode)
{
    uint8_t shift_w = pgm_read_byte(&flash_lights[id][0]);
    uint8_t shift_uv = pgm_read_byte(&flash_lights[id][1]);
    
    set_bit(lamps_memblock, shift_w, !!(mode & 0b01));
    set_bit(lamps_memblock, shift_uv, !!(mode & 0b10));
}

void drawing_light_set(enum drawing d, enum drawing_color c)
{
    uint8_t shift_r = pgm_read_byte(&drawings[d][0]);
    uint8_t shift_g = pgm_read_byte(&drawings[d][1]);
    uint8_t shift_b = pgm_read_byte(&drawings[d][2]);

    set_bit(drawings_memblock, shift_r, !!(c & 0b001));
    set_bit(drawings_memblock, shift_g, !!(c & 0b010));
    set_bit(drawings_memblock, shift_b, !!(c & 0b100));
}

void tv_noise_set(bool status)
{
    tv_status = status;
}

void room_mask_set(uint8_t mask)
{
    current_mask = mask;
}

static void apply_mask(uint8_t *memblock, uint8_t *maskslist, uint8_t size)
{
    uint8_t mask_byte;
    for (uint8_t i = 0; i < size; i++) {
        mask_byte = 0;
        for (uint8_t sh = 0; sh < 8; sh++) {
            if (current_mask & (1 << sh))
                mask_byte |= pgm_read_byte(maskslist + sh * size + i);
        }
        memblock[i] &= mask_byte;
    }
}

void house_reset(void)
{
    memset(lamps_memblock, 0, sizeof(lamps_memblock));
    memset(drawings_memblock, 0, sizeof(drawings_memblock));

    // Fill display with random content.
    ssd1306_begin_write();
    for (uint16_t i = 0; i < 128 * 8; i++) {
        ssd1306_write_byte(0xAA & rand());
    }
    ssd1306_end_write();
    ssd1306_display_off();

    tv_status = OFF;
    house_update();
}

void house_update(void)
{
    static uint8_t lamps_cache[4] = {0};
    static uint8_t drawings_cache[6] = {0};
    static bool tv_status_cache = OFF;

    uint8_t lamps_masked_memblock[4];
    memcpy(lamps_masked_memblock, lamps_memblock, sizeof(lamps_memblock));
    apply_mask(lamps_masked_memblock, (uint8_t *)lamps_memmasks, sizeof(lamps_memblock));
    if (memcmp(lamps_cache, lamps_masked_memblock, sizeof(lamps_cache))) {
        shiftreg_write_lamps(lamps_masked_memblock);
        memcpy(lamps_cache, lamps_masked_memblock, sizeof(lamps_cache));
    }

    uint8_t drawings_masked_memblock[6];
    memcpy(drawings_masked_memblock, drawings_memblock, sizeof(drawings_memblock));
    apply_mask(drawings_masked_memblock, (uint8_t *)drawings_memmasks, sizeof(drawings_memblock));
    if (memcmp(drawings_cache, drawings_masked_memblock, sizeof(drawings_cache))) {
        shiftreg_write_drawings(drawings_masked_memblock);
        memcpy(drawings_cache, drawings_masked_memblock, sizeof(drawings_cache));
    }

    bool tv_status_masked = tv_status && !!(current_mask & MASK_ROOM3);
    if (tv_status_cache != tv_status_masked) {
        if (tv_status_masked) {
            ssd1306_display_on();
            ssd1306_start_scrolling();
        } else {
            ssd1306_stop_scrolling();
            ssd1306_display_off();
        }
        tv_status_cache = tv_status_masked;
    }
}
