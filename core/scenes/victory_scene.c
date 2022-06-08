#include <game.h>
#include <scene.h>
#include <graphics.h>
#include <music.h>
#include <txt.h>
#include <tracks.h>

void victory_entrance_cb(const void *arg)
{
    const struct game_output *go = arg;
    
    gfx_set_scale(GFX_SCALE_X2);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_clear();
    gfx_print_txt_f(18, 0, txt_night_completed);

    gfx_set_color(GFX_COLOR_CYAN, GFX_COLOR_BLUE);
    gfx_print_txt_f(62, 50, txt_victory_cmt);

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_print_txt_f(0, 100, txt_attacks);
    gfx_print_dec(84, 100, go->score);

    music_start(&track_night_completed);
}

extern void gameover_exit_cb(void);

struct scene victory_scene = {NULL, victory_entrance_cb, NULL, gameover_exit_cb, 0};
