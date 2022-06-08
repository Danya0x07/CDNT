#include <menus.h>
#include <txt.h>
#include <game.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>

#include <avr/pgmspace.h>

extern void mainmenu_entrance_cb(struct menu *this);
extern void mainmenu_value_change_cb(struct menu *this);
extern void mainmenu_view_deinit_cb(struct menu *this);

static struct menu *nightmenu_exit_prev_cb(struct menu *this)
{
    return &main_menu;
}

static struct menu *nightmenu_exit_next_cb(struct menu *this)
{
    struct menu_field *field = &this->fields[0];
    struct game_input *gi = this->io;

    gi->request = GR_NEW_GAME;
    gi->night_no = field->value;

    return NULL;
}

static void nightmenu_view_init_cb(struct menu *this)
{
    static const PROGMEM uint8_t arrowup_bm[5] = {0x40, 0x20, 0x10, 0x20, 0x40};
    static const struct gfx_image arrowup = {
        .bitmap = arrowup_bm,
        .height = 8,
        .width = 5
    };

    static const PROGMEM uint8_t arrowdown_bm[5] = {0x01, 0x02, 0x04, 0x02, 0x01};
    static const struct gfx_image arrowdown = {
        .bitmap = arrowdown_bm,
        .height = 8,
        .width = 5
    };
    struct menu_field *field = &this->fields[0];

    gfx_set_scale(GFX_SCALE_X3);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_draw_image(126, 27, &arrowup);
    gfx_draw_image(126, 75, &arrowdown);

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_print_txt_f(18, 51, txt_night);
    gfx_print_dec(126, 51, field->value);
}

static void nightmenu_view_update_cb(struct menu *this)
{
    struct menu_field *field = &this->fields[0];
    gfx_print_dec(126, 51, field->value);
}

struct menu night_menu = {
    .fields = (struct menu_field []) {
        {1, 1, 5, true},
    },
    .labels = (const char *[]) {txt_night},
    .io = NULL,
    .on_entrance = mainmenu_entrance_cb,
    .on_value_change = mainmenu_value_change_cb,
    .on_cursor_move = NULL,
    .on_exit_next = nightmenu_exit_next_cb,
    .on_exit_prev = nightmenu_exit_prev_cb,
    .view_init = nightmenu_view_init_cb,
    .view_update = nightmenu_view_update_cb,
    .view_deinit = mainmenu_view_deinit_cb,
    .num_fields = 1,
    .num_labels = 1,
    .cursor = 0
};