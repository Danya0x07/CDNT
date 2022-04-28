#include "music.h"
#include <avr/pgmspace.h>
#include <hal/timers.h>

static const PROGMEM uint16_t track_1[][2] = {
    {400, 800}, {900, 600}, {400, 800}, {640, 200}, {700, 600},
};

struct track {
    const uint16_t (*notes)[2];
    const uint8_t len;
};

static struct track tracks[M_TRACKS_NUMBER] = {
    {track_1, sizeof(track_1) / sizeof(track_1[0])},
};

static enum music_track current_track = M_SILENCE;
static uint8_t note_idx = 0;

void music_play(enum music_track track)
{
    music_stop();
    current_track = track;
}

enum music_track music_playing(void)
{
    return current_track != M_SILENCE || meander_emitting();
}

void music_stop(void)
{
    meander_stop();
    current_track = M_SILENCE;
    note_idx = 0;
}

void music_update(void)
{
    if (current_track == M_SILENCE)
        return;
    
    if (!meander_emitting()) {
        struct track *tr = &tracks[current_track];
        if (note_idx > tr->len - 1) { // last note ended
            music_stop();
        } else {
            uint16_t note = pgm_read_word(&tr->notes[note_idx][0]);
            uint16_t duration = pgm_read_word(&tr->notes[note_idx][1]);
            meander_emit(note, duration);
            note_idx++;
        }          
    }
}
