#ifndef _HAL_SPI_H
#define _HAL_SPI_H

#include <stdint.h>

void spi_init(void);
uint8_t spi_transfer_byte(uint8_t b);
void spi_transfer_bytes(uint8_t *in, const uint8_t *out, uint8_t len);

#endif  // _HAL_SPI_H