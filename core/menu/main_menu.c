#include <menus.h>
#include <txt.h>
#include <game.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>

#include <avr/pgmspace.h>

#include "common.h"

static struct menu *mainmenu_exit_prev_cb(struct menu *this)
{
    return this;
}

static struct menu *mainmenu_exit_next_cb(struct menu *this)
{
    if (this->fields[0].value == 1) {
        return &instr_menu;
    } else {
        return &night_menu;
    }
}

static void mainmenu_view_init_cb(struct menu *this)
{
    gfx_clear();
    
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X3);
    gfx_print_txt_f(18, 0, txt_gl_title);

    gfx_set_color(GFX_COLOR_MAGENTA, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X1);
    gfx_print_txt_f(70, 48, txt_gl_subtitle);

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X2);
    gfx_print_txt_f(18, 70, (const char *)pgm_read_word(&this->labels[0]));
    gfx_print_txt_f(18, 90, (const char *)pgm_read_word(&this->labels[1]));
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_print_ch(0, 70, '>');

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X1);
    gfx_print_txt_f(135, 119, txt_gl_version);
}

static void mainmenu_view_update_cb(struct menu *this)
{
    gfx_clear_rect(0, 70, 12, 40);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X2);
    gfx_print_ch(0, 70 + 20 * this->fields[0].value, '>');
}

struct menu main_menu = {
    .fields = (struct menu_field []) {
        {0, 0, 1, false},
    },
    .labels = (const char **)txt_mainmenu,
    .io = NULL,
    .on_entrance = common_entrance_cb,
    .on_value_change = common_value_change_cb,
    .on_cursor_move = NULL,
    .on_exit_next = mainmenu_exit_next_cb,
    .on_exit_prev = mainmenu_exit_prev_cb,
    .view_init = mainmenu_view_init_cb,
    .view_update = mainmenu_view_update_cb,
    .view_deinit = common_view_deinit_cb,
    .num_fields = 1,
    .num_labels = 2,
    .cursor = 0
};