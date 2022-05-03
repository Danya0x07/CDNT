/** Tiny music player submodule.
 * No difference between short sounds and long melodies.
 * Asyncronous note changing. Blank notes supported.
 */

#ifndef _MUSIC_H
#define _MUSIC_H

#include <stdint.h>
#include <stdbool.h>

/* Music track structure.
 * `notes` is an array of couples of uint16_t's, each couple is
 * a note and it's duration respectively. `notes` must be stored in Flash.
 */
struct music_track {
    const uint16_t (*notes)[2];
    uint8_t len;
};

/* Start playing given track.
 * If other track is being played, it is interrupted. */
void music_play(const struct music_track *track);

// Is something being played now.
bool music_playing(void);

// Stop playing
void music_stop(void);

// Move to the next note of track if current one is over.
void music_update(void);

#endif  // _MUSIC_H