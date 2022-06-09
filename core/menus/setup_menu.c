#include <menus.h>
#include <txt.h>
#include <img.h>
#include <game.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>
#include <config.h>

extern void mainmenu_value_change_cb(struct menu *this);
extern void mainmenu_view_deinit_cb(struct menu *this);

static void setupmenu_entrance_cb(struct menu *this)
{
    for (uint8_t i = 0; i < NUM_OF_ENTITIES; i++) {
        this->fields[i].value = 0;
    }
    this->cursor = 0;
}

static void setupmenu_cursor_move_cb(struct menu *this)
{
    music_play(&track_cursor_move);
}

static struct menu *setupmenu_exit_prev_cb(struct menu *this)
{
    return &night_menu;
}

static struct menu *setupmenu_exit_next_cb(struct menu *this)
{
    extern uint8_t custom_activities[NUM_OF_ENTITIES];

    for (uint8_t i = 0; i < NUM_OF_ENTITIES; i++) {
        custom_activities[i] = this->fields[i].value;
    }
    return NULL;
}

static void setupmenu_view_init_cb(struct menu *this)
{
    gfx_set_scale(GFX_SCALE_X2);
    gfx_set_color(GFX_COLOR_MAGENTA, GFX_COLOR_BLACK);
    gfx_print_txt_f(8, 0, txt_custom_night);
    gfx_set_scale(GFX_SCALE_X1);
    gfx_print_txt_f(65, 18, txt_setup);

    gfx_set_color(GFX_COLOR_YELLOW, GFX_COLOR_BLACK);
    gfx_draw_image(2, 50, &img_ghost);
    gfx_set_color(GFX_COLOR_BLUE, GFX_COLOR_BLACK);
    gfx_draw_image(34, 50, &img_ghost);
    gfx_set_color(GFX_COLOR_RED, GFX_COLOR_BLACK);
    gfx_draw_image(66, 50, &img_ghost);
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_draw_image(98, 50, &img_lamp_poltergeist);
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_draw_image(130, 50, &img_cam_poltergeist);

    gfx_set_scale(GFX_SCALE_X2);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    for (uint8_t i = 0; i < NUM_OF_ENTITIES; i++) {
        gfx_draw_image(10 + 32 * i, 76, &img_arrowup);
        gfx_draw_image(10 + 32 * i, 110, &img_arrowdown);
    }

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    for (uint8_t i = 0; i < NUM_OF_ENTITIES; i++) {
        gfx_print_ch(10 + 32 * i, 93, '0');
    }
    
    gfx_set_color(GFX_COLOR_MAGENTA, GFX_COLOR_BLACK);
    gfx_draw_frame(2, 91, 26, 18, 1);
}

static void setupmenu_view_update_cb(struct menu *this)
{
    struct menu_field *field = &this->fields[this->cursor];
    uint8_t x = 10;

    if (field->value >= 10)
        x = 4;
    
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    for (uint8_t i = 0; i < NUM_OF_ENTITIES; i++) {
        gfx_clear_rect(2 + 32 * i, 91, 1, 18);
        gfx_clear_rect(27 + 32 * i, 91, 1, 18);
    }
    gfx_clear_rect(2, 91, 158, 1);
    gfx_clear_rect(2, 108, 158, 1);
    
    gfx_clear_rect(4 + 32 * this->cursor, 91, 26, 18);
    gfx_print_dec(x + 32 * this->cursor, 93, field->value);

    gfx_set_color(GFX_COLOR_MAGENTA, GFX_COLOR_BLACK);
    gfx_draw_frame(2 + 32 * this->cursor, 91, 26, 18, 1);
}

struct menu setup_menu = {
    .fields = (struct menu_field []) {
        {0, 0, MAX_ACTIVITY_LVL, true},
        {0, 0, MAX_ACTIVITY_LVL, true},
        {0, 0, MAX_ACTIVITY_LVL, true},
        {0, 0, MAX_ACTIVITY_LVL, true},
        {0, 0, MAX_ACTIVITY_LVL, true},
    },
    .labels = NULL,
    .io = NULL,
    .on_entrance = setupmenu_entrance_cb,
    .on_value_change = mainmenu_value_change_cb,
    .on_cursor_move = setupmenu_cursor_move_cb,
    .on_exit_next = setupmenu_exit_next_cb,
    .on_exit_prev = setupmenu_exit_prev_cb,
    .view_init = setupmenu_view_init_cb,
    .view_update = setupmenu_view_update_cb,
    .view_deinit = mainmenu_view_deinit_cb,
    .num_fields = 5,
    .num_labels = 0,
    .cursor = 0
};