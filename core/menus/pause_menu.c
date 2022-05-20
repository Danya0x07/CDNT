#include <menus.h>
#include <txt.h>
#include <game.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>

#include <avr/pgmspace.h>

#define CHOICE_CONTINUE 0
#define CHOICE_EXIT     1 

extern void mainmenu_entrance_cb(struct menu *this);
extern void mainmenu_value_change_cb(struct menu *this);
extern void mainmenu_view_update_cb(struct menu *this);
extern void mainmenu_view_deinit_cb(struct menu *this);
extern struct menu *mainmenu_exit_prev_cb(struct menu *this);

struct menu *pausemenu_exit_next_cb(struct menu *this)
{
    struct menu_field *field = &this->fields[0];
    struct game_input *gi = this->io;

    gi->action = ACTION_CONTINUE;
    return field->value == CHOICE_CONTINUE ? NULL : &main_menu;
}

void pausemenu_view_init_cb(struct menu *this)
{
    struct game_output *go = this->io;

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X3);
    gfx_print_txt_f(35, 0, txt_pause);

    gfx_set_scale(GFX_SCALE_X1);
    gfx_print_txt_f(53, 30, txt_night);
    gfx_print_ch(77, 30, ':');
    gfx_print_dec(95, 30, go->night_no);
    gfx_print_txt_f(53, 40, txt_hours);
    gfx_print_dec(95, 40, go->hours_survived);
    gfx_print_txt_f(53, 50, txt_attacks);
    gfx_print_dec(95, 50, go->attacks_repelled);

    gfx_set_scale(GFX_SCALE_X2);
    gfx_print_txt_f(18, 70, txt_continue);
    gfx_print_txt_f(18, 90, txt_exit);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_print_ch(0, 70, '>');
}

struct menu pause_menu = {
    .fields = (struct menu_field []) {
        {0, 0, 1, true},
    },
    .labels = NULL,
    .io = NULL,
    .on_entrance = mainmenu_entrance_cb,
    .on_value_change = mainmenu_value_change_cb,
    .on_cursor_move = NULL,
    .on_exit_next = pausemenu_exit_next_cb,
    .on_exit_prev = mainmenu_exit_prev_cb,
    .view_init = pausemenu_view_init_cb,
    .view_update = mainmenu_view_update_cb,
    .view_deinit = mainmenu_view_deinit_cb,
    .num_fields = 1,
    .num_labels = 2,
    .cursor = 0
};