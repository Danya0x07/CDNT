#include "spi.h"
#include <avr/io.h>
#include <stddef.h>

#define DD_SPI  DDRB
#define MOSI    _BV(PB3)
#define MISO    _BV(PB4)
#define SCK     _BV(PB5)
#define SS      _BV(PB2)

void spi_init(void)
{
    DD_SPI |= MOSI | SCK | SS;
    DD_SPI &= ~MISO;
    SPCR = _BV(SPE) | _BV(MSTR)|(1<<SPR1)|(1<<SPR0);  // mode 0, 1/4 from Fosc, MSB first.
}

uint8_t spi_transfer_byte(uint8_t b)
{
    SPDR = b;
    loop_until_bit_is_set(SPSR, SPIF);
    return SPDR;
}

void spi_transfer_bytes(uint8_t *in, const uint8_t *out, uint8_t len)
{
    if (in == NULL) {
        while (len--)
            spi_transfer_byte(*out++);
    } else if (out == NULL) {
        while (len--)
            *in++ = spi_transfer_byte(0);
    } else {
        while (len--)
            *in++ = spi_transfer_byte(*out++);
    }
}
