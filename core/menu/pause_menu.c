#include <menus.h>
#include <txt.h>
#include <game.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>

#include <avr/pgmspace.h>

#include "common.h"

#define CHOICE_CONTINUE 0
#define CHOICE_EXIT     1 

static struct menu *pause_exit_prev_cb(struct menu *this)
{
    struct game_input *ginp = this->io;
    ginp->action = CONTINUE;
    return NULL;
}

static struct menu *pause_exit_next_cb(struct menu *this)
{
    struct game_input *ginp = this->io;
    uint8_t choice = this->fields[0].value;
    ginp->action = CONTINUE;
    return choice == CHOICE_CONTINUE ? NULL : &main_menu;
}

static void pause_view_init_cb(struct menu *this)
{
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X3);
    gfx_print_txt_f(35, 0, txt_ml_pause);

    gfx_set_scale(GFX_SCALE_X2);
    gfx_print_txt_f(18, 70, (const char *)pgm_read_word(&this->labels[0]));
    gfx_print_txt_f(18, 90, (const char *)pgm_read_word(&this->labels[1]));
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_print_ch(0, 70, '>');
}

static void pause_view_update_cb(struct menu *this)
{
    gfx_clear_rect(0, 70, 12, 40);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X2);
    gfx_print_ch(0, 70 + 20 * this->fields[0].value, '>');
}

struct menu pause_menu = {
    .fields = (struct menu_field []) {
        {0, 0, 1, true},
    },
    .labels = (const char **)txt_pausemenu,
    .io = NULL,
    .on_entrance = common_entrance_cb,
    .on_value_change = common_value_change_cb,
    .on_cursor_move = NULL,
    .on_exit_next = pause_exit_next_cb,
    .on_exit_prev = pause_exit_prev_cb,
    .view_init = pause_view_init_cb,
    .view_update = pause_view_update_cb,
    .view_deinit = common_view_deinit_cb,
    .num_fields = 1,
    .num_labels = 2,
    .cursor = 0
};