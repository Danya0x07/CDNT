#include <menu.h>
#include <txt.h>
#include <game.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>

#include <avr/pgmspace.h>

static void nightmenu_entrance_cb(struct menu *this)
{
    this->fields[0].value = this->fields[0].min;
}

static void nightmenu_value_change_cb(struct menu *this)
{
    music_play(&track_value_change);
}

static struct menu *nightmenu_exit_prev_cb(struct menu *this)
{
    extern struct menu main_menu;
    return &main_menu;
}

static struct menu *nightmenu_exit_next_cb(struct menu *this)
{
    struct game_input *ginp = this->io;
    ginp->action = NEW_GAME;
    ginp->night_no = this->fields[0].value;
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

    gfx_set_scale(GFX_SCALE_X3);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_draw_image(126, 27, &arrowup);
    gfx_draw_image(126, 75, &arrowdown);

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_print_txt_f(18, 51, txt_ml_night);
    gfx_print_ch(126, 51, '0' + this->fields[0].value);
}

static void nightmenu_view_update_cb(struct menu *this)
{
    gfx_print_ch(126, 51, '0' + this->fields[0].value);
}

static void nightmenu_view_deinit_cb(struct menu *this)
{
    music_play(&track_screen_transit);
    gfx_clear();
}

struct menu night_menu = {
    .fields = (struct menu_field []) {
        {1, 1, 5, true},
    },
    .labels = (const char *[]) {txt_ml_night},
    .io = NULL,
    .on_entrance = nightmenu_entrance_cb,
    .on_value_change = nightmenu_value_change_cb,
    .on_cursor_move = NULL,
    .on_exit_next = nightmenu_exit_next_cb,
    .on_exit_prev = nightmenu_exit_prev_cb,
    .view_init = nightmenu_view_init_cb,
    .view_update = nightmenu_view_update_cb,
    .view_deinit = nightmenu_view_deinit_cb,
    .num_fields = 1,
    .num_labels = 1,
    .cursor = 0
};