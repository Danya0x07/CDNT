#include <game.h>
#include <scene.h>
#include <graphics.h>
#include <music.h>
#include <txt.h>
#include <tracks.h>

void gameover_entrance_cb(const void *arg)
{
    const struct game_output *go = arg;
    
    gfx_set_scale(GFX_SCALE_X2);
    gfx_set_color(GFX_COLOR_RED, GFX_COLOR_BLACK);
    gfx_clear();
    gfx_print_txt_f(18, 0, txt_night_failed);

    gfx_set_color(GFX_COLOR_MAGENTA, GFX_COLOR_RED);
    gfx_print_txt_f(62, 50, txt_gameover_cmt);

    gfx_set_color(GFX_COLOR_RED, GFX_COLOR_BLACK);
    gfx_print_txt_f(0, 80, txt_hours);
    gfx_print_dec(84, 80, go->hour);
    gfx_print_txt_f(0, 100, txt_attacks);
    gfx_print_dec(84, 100, go->score);

    music_start(&track_night_failed);
}

void gameover_exit_cb(void)
{
    music_play(&track_screen_transit);
    gfx_clear();
}

struct scene gameover_scene = {NULL, gameover_entrance_cb, NULL, gameover_exit_cb, 0};
