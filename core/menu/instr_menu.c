#include <menus.h>
#include <txt.h>
#include <game.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>

#include <avr/pgmspace.h>

#include "common.h"

static struct menu *instrmenu_exit_prev_cb(struct menu *this)
{
    return &main_menu;
}

static struct menu *instrmenu_exit_next_cb(struct menu *this)
{
    return this;
}

static void instrmenu_view_init_cb(struct menu *this)
{
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X1);
    gfx_print_txt_f(0, 0, (const char *)pgm_read_word(&this->labels[0]));
    gfx_print_txt(71, 119, "1/3");
}

static void instrmenu_view_update_cb(struct menu *this)
{
    gfx_clear_rect(0, 0, 160, 119);
    gfx_print_txt_f(0, 0, (const char *)pgm_read_word(&this->labels[this->fields[0].value]));
    gfx_print_ch(71, 119, '1' + this->fields[0].value);
}

struct menu instr_menu = {
    .fields = (struct menu_field []) {
        {0, 0, 2, false},
    },
    .labels = (const char **)txt_instrmenu,
    .io = NULL,
    .on_entrance = common_entrance_cb,
    .on_value_change = common_value_change_cb,
    .on_cursor_move = NULL,
    .on_exit_next = instrmenu_exit_next_cb,
    .on_exit_prev = instrmenu_exit_prev_cb,
    .view_init = instrmenu_view_init_cb,
    .view_update = instrmenu_view_update_cb,
    .view_deinit = common_view_deinit_cb,
    .num_fields = 1,
    .num_labels = 3,
    .cursor = 0
};