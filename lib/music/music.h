/** Tiny music player submodule.
 * No difference between short sounds and long melodies.
 * Asyncronous note changing.
 */

#ifndef _MUSIC_H
#define _MUSIC_H

#include <stdint.h>
#include <stdbool.h>

// Status codes.
#define MUSIC_OK    0
#define MUSIC_ERROR (-1)

enum music_track {
    M_TR1,
    M_TRACKS_NUMBER,
    M_SILENCE = 255
};

/* Start playing given track.
 * If other track is being played, it is interrupted. */
void music_play(enum music_track track);

// What is being played now.
enum music_track music_playing(void);

// Stop playing
void music_stop(void);

// Move to the next note of track if current one is over.
void music_update(void);

#endif  // _MUSIC_H