#ifndef _HAL_ADC_H
#define _HAL_ADC_H

#include <avr/io.h>
#include <stdbool.h>

void adc_init(void);

void adc_start_conversion(uint8_t ch);
bool adc_conversion_complete(void);
uint16_t adc_read_value(void);

uint16_t adc_measure(uint8_t ch);

#endif  // _HAL_ADC_H