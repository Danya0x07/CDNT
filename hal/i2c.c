#include "i2c.h"
#include <avr/io.h>

void i2c_init(void)
{
    TWSR = 0;
    TWBR = ((F_CPU / 400000) - 16) >> 1; // 400 kHz
}

void i2c_start(uint8_t addr, uint8_t direction)
{
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    loop_until_bit_is_set(TWCR, TWINT);

    TWDR = (addr & 0xFE) | (direction & 0x01);
    TWCR = _BV(TWINT) | _BV(TWEN);
    loop_until_bit_is_set(TWCR, TWINT);
}

void i2c_stop(void)
{
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
    loop_until_bit_is_clear(TWCR, TWSTO);
}

void i2c_write_byte(uint8_t b)
{
    TWDR = b;
    TWCR = _BV(TWINT) | _BV(TWEN);
    loop_until_bit_is_set(TWCR, TWINT);
}

static void i2c_write(const uint8_t *data, uint16_t len)
{
    while (len--)
        i2c_write_byte(*data++);
}

static void i2c_read(uint8_t *data, uint8_t len)
{
    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN);
    for (; len; len--) {
        if (len == 1) {
            TWCR = _BV(TWINT) | _BV(TWEN);
        }
        loop_until_bit_is_set(TWCR, TWINT);
        *data++ = TWDR;
    }
}

void i2c_write_bytes(uint8_t addr, const uint8_t *data, uint16_t len, 
                     uint8_t flags)
{
    if (!(flags & I2C_NOSTART))
        i2c_start(addr, I2C_DIRECTION_TX);
    i2c_write(data, len);
    if (!(flags & I2C_NOSTOP))
        i2c_stop();
}

void i2c_read_bytes(uint8_t addr, uint8_t *data, uint16_t len, 
                    uint8_t flags)
{
    if (!(flags & I2C_NOSTART))
        i2c_start(addr, I2C_DIRECTION_RX);
    i2c_read(data, len);
    if (!(flags & I2C_NOSTOP))
        i2c_stop();
}