#include <game.h>
#include <scene.h>
#include <graphics.h>
#include <music.h>
#include <txt.h>
#include <tracks.h>

#include <avr/pgmspace.h>

#define QUESTION    0
#define ANSWER      1

void dialog_entrance_cb(const void *arg)
{
    const struct game_input *gi = arg;
    const char *txt = (const char *)pgm_read_word(&txts_dialogs[gi->night_no - 1][QUESTION]);
    
    gfx_clear();
    gfx_set_scale(GFX_SCALE_X1);
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_print_ch(0, 0, '>');
    gfx_set_color(GFX_COLOR_CYAN, GFX_COLOR_BLACK);
    gfx_print_txt_f(0, 0, txt);
    music_start(&track_irc_typing);
}

void dialog_stage_cb(const void *arg, uint8_t stage)
{
    const struct game_input *gi = arg;
    const char *txt = (const char *)pgm_read_word(&txts_dialogs[gi->night_no - 1][ANSWER]);
    
    gfx_set_color(GFX_COLOR_GREEN, GFX_COLOR_BLACK);
    gfx_print_ch(0, 24, '>');
    gfx_set_color(GFX_COLOR_MAGENTA, GFX_COLOR_BLACK);
    gfx_print_txt_f(0, 24, txt);
    music_start(&track_irc_typing);
}

void dialog_exit_cb(void)
{
    gfx_clear();
    music_start(&track_night_begins);
}

struct scene dialog_scene = {NULL, dialog_entrance_cb, dialog_stage_cb, dialog_exit_cb, 1};
