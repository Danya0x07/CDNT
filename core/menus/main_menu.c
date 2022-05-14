#include <menus.h>
#include <txt.h>
#include <game.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>

#include <avr/pgmspace.h>

#define CHOICE_PLAY 0
#define CHOICE_INSTRUCTIONS 1

void mainmenu_entrance_cb(struct menu *this)
{
    struct menu_field *field = &this->fields[0];
    field->value = field->min;
}

void mainmenu_value_change_cb(struct menu *this)
{
    music_play(&track_value_change);
}

struct menu *mainmenu_exit_prev_cb(struct menu *this)
{
    return this;
}

struct menu *mainmenu_exit_next_cb(struct menu *this)
{
    struct menu_field *field = &this->fields[0];
    
    if (field->value == CHOICE_INSTRUCTIONS)
        return &instr_menu;
    else
        return &night_menu;
}

void mainmenu_view_init_cb(struct menu *this)
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
    gfx_print_txt_f(18, 70, (const char *)pgm_read_word(&this->labels[CHOICE_PLAY]));
    gfx_print_txt_f(18, 90, (const char *)pgm_read_word(&this->labels[CHOICE_INSTRUCTIONS]));
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_print_ch(0, 70, '>');

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X1);
    gfx_print_txt_f(135, 119, txt_gl_version);
}

void mainmenu_view_update_cb(struct menu *this)
{
    struct menu_field *field = &this->fields[0];

    gfx_clear_rect(0, 70, 12, 40);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X2);
    gfx_print_ch(0, 70 + 20 * field->value, '>');
}

void mainmenu_view_deinit_cb(struct menu *this)
{
    music_play(&track_screen_transit);
    gfx_clear();
}

struct menu main_menu = {
    .fields = (struct menu_field []) {
        {0, 0, 1, false},
    },
    .labels = (const char **)txt_mainmenu,
    .io = NULL,
    .on_entrance = mainmenu_entrance_cb,
    .on_value_change = mainmenu_value_change_cb,
    .on_cursor_move = NULL,
    .on_exit_next = mainmenu_exit_next_cb,
    .on_exit_prev = mainmenu_exit_prev_cb,
    .view_init = mainmenu_view_init_cb,
    .view_update = mainmenu_view_update_cb,
    .view_deinit = mainmenu_view_deinit_cb,
    .num_fields = 1,
    .num_labels = 2,
    .cursor = 0
};