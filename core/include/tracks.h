#ifndef _CORE_TRACKS_H
#define _CORE_TRACKS_H

#include <music.h>

#define DECLARE_TRACK(name) \
extern struct music_track track_##name

DECLARE_TRACK(value_change);
DECLARE_TRACK(cursor_move);
DECLARE_TRACK(screen_transit);
DECLARE_TRACK(intro);
DECLARE_TRACK(game_start);
DECLARE_TRACK(night_complete);
DECLARE_TRACK(game_over);
DECLARE_TRACK(cam_switch);
DECLARE_TRACK(cam_uv_switch);
DECLARE_TRACK(flash);
DECLARE_TRACK(power_off);
DECLARE_TRACK(lamps_on);
DECLARE_TRACK(lamps_off);
DECLARE_TRACK(irc_typing);
DECLARE_TRACK(cam_nosignal);
DECLARE_TRACK(screamer1);
DECLARE_TRACK(screamer2);
DECLARE_TRACK(screamer3);

// Some tracks use same notes.
#define track_pause         track_screen_transit
#define track_continue      track_screen_transit
#define track_option_move   track_value_change
#define track_power_on      track_intro

#endif // _CORE_TRACKS_H