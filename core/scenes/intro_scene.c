#include <game.h>
#include <scene.h>
#include <graphics.h>
#include <music.h>
#include <txt.h>
#include <tracks.h>

void intro_entrance_cb(const void *arg)
{
    gfx_clear();
    gfx_set_scale(GFX_SCALE_X3);
    music_start(&track_intro);
}

void intro_stage_cb(const void *arg, uint8_t stage)
{
    gfx_print_ch((stage - 1) * 18, 0, '.');
}

extern void gameover_exit_cb(void);

struct scene intro_scene = {NULL, intro_entrance_cb, intro_stage_cb, gameover_exit_cb, 3};
