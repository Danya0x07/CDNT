#include <menus.h>
#include <txt.h>
#include <img.h>
#include <game.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>

extern void mainmenu_entrance_cb(struct menu *this);
extern void mainmenu_view_deinit_cb(struct menu *this);

static void nightmenu_value_change_cb(struct menu *this)
{
    static bool setup_menu_available = false;
    static uint8_t last_value = 1;
    static uint8_t try_count = 0;
    struct menu_field *field = &this->fields[0];

    if (!setup_menu_available && field->value != last_value) {
        if (last_value == 5 && field->value == 1) {
            try_count++;
            if (try_count >= 3) {
                field->min = 0;
                setup_menu_available = true;
            }
        }
        last_value = field->value;
    }

    music_play(&track_value_change);
}

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

    return field->value ? NULL : &setup_menu;
}

static void nightmenu_view_init_cb(struct menu *this)
{
    struct menu_field *field = &this->fields[0];

    gfx_set_scale(GFX_SCALE_X3);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_draw_image(126, 27, &img_arrowup);
    gfx_draw_image(126, 75, &img_arrowdown);

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
    .on_value_change = nightmenu_value_change_cb,
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