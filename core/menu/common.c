#include <menu.h>
#include <music.h>
#include <tracks.h>
#include <graphics.h>

void common_entrance_cb(struct menu *this)
{
    this->fields[0].value = this->fields[0].min;
}

void common_value_change_cb(struct menu *this)
{
    music_play(&track_value_change);
}

void common_view_deinit_cb(struct menu *this)
{
    music_play(&track_screen_transit);
    gfx_clear();
}