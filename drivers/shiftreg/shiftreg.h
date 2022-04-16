#ifndef _SHIFTREG_H
#define _SHIFTREG_H

#include <stdint.h>

void shiftreg_write_lamps(uint8_t content[4]);
void shiftreg_write_drawings(uint8_t content[6]);
uint8_t shiftreg_read_buttons(void);


#endif  // _SHIFTREG_H