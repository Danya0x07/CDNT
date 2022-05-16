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
extern struct menu *mainmenu_exit_prev_cb(struct menu *this);

struct menu *instrmenu_exit_prev_cb(struct menu *this)
{
    return &main_menu;
}

void instrmenu_view_update_cb(struct menu *this)
{
    struct menu_field *field = &this->fields[0];
    uint8_t x;

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X1);
    gfx_clear_rect(0, 0, 160, 119);
    gfx_print_txt_f(0, 0, (const char *)pgm_read_word(&this->labels[field->value]));
    x = gfx_print_dec(71, 119, 1 + field->value);
    gfx_print_txt(x, 119, "/3");
}

struct menu instr_menu = {
    .fields = (struct menu_field []) {
        {0, 0, 2, false},
    },
    .labels = (const char **)txts_instructions,
    .io = NULL,
    .on_entrance = mainmenu_entrance_cb,
    .on_value_change = mainmenu_value_change_cb,
    .on_cursor_move = NULL,
    .on_exit_next = mainmenu_exit_prev_cb,
    .on_exit_prev = instrmenu_exit_prev_cb,
    .view_init = instrmenu_view_update_cb,
    .view_update = instrmenu_view_update_cb,
    .view_deinit = mainmenu_view_deinit_cb,
    .num_fields = 1,
    .num_labels = 3,
    .cursor = 0
};