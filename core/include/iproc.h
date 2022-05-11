#ifndef _CORE_IPROC_H
#define _CORE_IPROC_H

#include <stdint.h>

#include <joystick.h>
#include <iev.h>

// Process joystick events.
enum joystick_event iproc_joystick(enum joystick_position pos);

/* Process buttons events
 *
 * Return byte format:  0000|0000
 * Recently       released ^    ^ pressed
 * button number (1..7 or 0 if not). */
uint8_t iproc_buttons(uint8_t b);

#endif // _CORE_IPROC_H