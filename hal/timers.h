#ifndef _HAL_TIMERS_H
#define _HAL_TIMERS_H

#include <avr/io.h>
#include <stdbool.h>

// Initialize all needed timers.
void timers_init(void);

// Return milliseconds passed from startup.
uint32_t ms_passed(void);

// Blocking milliseconds delay function.
void ms_wait(uint32_t ms);

/* Start meander with a given frequency (Hz).
 * Reasonable range is 200...4000. */
void meander_start(uint16_t freq);

// Stop generating meander.
void meander_stop(void);

/* Emit meander with a given frequency (Hz)
 * for given time (ms). No blocking.*/
void meander_emit(uint16_t freq, uint16_t duration);

// Is meander being emitted now?
bool meander_emitting(void);

#endif  // _HAL_TIMERS_H