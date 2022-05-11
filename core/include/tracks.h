#ifndef _CORE_TRACKS_H
#define _CORE_TRACKS_H

#include <music.h>

#define DECLARE_TRACK(name) \
extern struct music_track name##_track

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
#define pause_track         screen_transit_track
#define continue_track      screen_transit_track
#define option_move_track   value_change_track
#define power_on_track      intro_track

#endif // _CORE_TRACKS_H