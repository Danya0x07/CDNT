#include <avr/interrupt.h>

#include <hal/adc.h>
#include <hal/spi.h>
#include <hal/i2c.h>
#include <hal/timers.h>
#include <hal/uart.h>

#include <joystick.h>
#include <serial.h>
#include <shiftreg.h>
#include <ssd1306.h>
#include <st7735.h>

void init_hal(void)
{
    adc_init();
    spi_init();
    i2c_init();
    timers_init();
    uart_init();
    sei();
}

void init_drivers(void)
{
    shiftreg_init();
    ssd1306_init();
    st7735_init();
}