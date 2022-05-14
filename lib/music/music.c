#include "music.h"
#include <avr/pgmspace.h>
#include <hal/timers.h>
#include <stddef.h>

static const struct music_track *current_track = NULL;
static uint8_t note_idx = 0;

void music_start(const struct music_track *track)
{
    music_stop();
    current_track = track;
}

bool music_playing(void)
{
    return current_track || meander_emitting();
}

void music_stop(void)
{
    meander_stop();
    current_track = NULL;
    note_idx = 0;
}

void music_play(const struct music_track *track)
{
    music_start(track);
    while (music_playing())
        music_update();
    music_stop();
}

void music_update(void)
{ 
    if (current_track && !meander_emitting()) {
        if (note_idx >= current_track->len) { // last note ended
            music_stop();
        } else {
            static uint32_t now;
            uint16_t note, duration;
            
            if (current_track->progmem) {
                note = pgm_read_word(&current_track->notes[note_idx][0]);
                duration = pgm_read_word(&current_track->notes[note_idx][1]);
            } else {
                note = current_track->notes[note_idx][0];
                duration = current_track->notes[note_idx][1];
            }
            
            if (note) {
                meander_emit(note, duration);
                now = 0;
                note_idx++;
            } else {
                if (!now)
                    now = ms_passed();
                if (ms_passed() - now >= duration)
                    note_idx++;
            }
        }          
    }
}
