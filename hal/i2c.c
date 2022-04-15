#include "i2c.h"
#include <avr/io.h>

#define I2C_DIRECTION_TX    0
#define I2C_DIRECTION_RX    1

void i2c_init(void)
{
    TWBR = 12; // 400 kHz
}

static void i2c_start(uint8_t addr, uint8_t direction)
{
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    loop_until_bit_is_set(TWCR, TWINT);

    TWDR = addr & 0xFE | direction & 0x01;
    TWCR = _BV(TWINT) | _BV(TWEN);
    loop_until_bit_is_set(TWCR, TWINT);
}

static void i2c_stop(void)
{
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

static void i2c_write(const uint8_t *data, uint8_t len)
{
    while (len--) {
        TWDR = *data++;
        TWCR = _BV(TWINT) | _BV(TWEN);
        loop_until_bit_is_set(TWCR, TWINT);
    }
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

void i2c_write_bytes(uint8_t addr, const uint8_t *data, uint8_t len, 
                     uint8_t flags)
{
    if (!(flags & I2C_NOSTART))
        i2c_start(addr, I2C_DIRECTION_TX);
    i2c_write(data, len);
    if (!(flags & I2C_NOSTOP))
        i2c_stop();
}

void i2c_read_bytes(uint8_t addr, uint8_t *data, uint8_t len, 
                    uint8_t flags)
{
    if (!(flags & I2C_NOSTART))
        i2c_start(addr, I2C_DIRECTION_RX);
    i2c_read(data, len);
    if (!(flags & I2C_NOSTOP))
        i2c_stop();
}