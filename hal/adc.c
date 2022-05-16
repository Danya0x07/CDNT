#include "adc.h"
#include <avr/io.h>

void adc_init(void)
{
    // divider 8
    ADMUX = _BV(REFS0);
    ADCSRA = _BV(ADEN) | _BV(ADPS1) | _BV(ADPS0);
}

void adc_start_conversion(uint8_t ch)
{
    ADMUX &= ~(_BV(MUX3) | _BV(MUX2)| _BV(MUX1) | _BV(MUX0));
    ADMUX |= (ch & 7);
    ADCSRA |= _BV(ADSC);
}

bool adc_conversion_complete(void)
{
    return bit_is_clear(ADCSRA, ADSC);
}

uint16_t adc_read_value(void)
{
    return ADC;
}

uint16_t adc_measure(uint8_t ch)
{
    adc_start_conversion(ch);
    loop_until_bit_is_clear(ADCSRA, ADSC);
    return ADC;
}