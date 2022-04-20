#ifndef _HAL_I2C_H
#define _HAL_I2C_H

#include <stdint.h>

#define I2C_DIRECTION_TX    0
#define I2C_DIRECTION_RX    1

#define I2C_NOSTART (1 << 0)
#define I2C_NOSTOP  (1 << 1)

void i2c_init(void);
void i2c_start(uint8_t addr, uint8_t direction);
void i2c_write_byte(uint8_t b);
void i2c_stop(void);
void i2c_write_bytes(uint8_t addr, const uint8_t *data, uint16_t len, 
                     uint8_t flags);
void i2c_read_bytes(uint8_t addr, uint8_t *data, uint16_t len, 
                    uint8_t flags);

#endif  // _HAL_I2C_H