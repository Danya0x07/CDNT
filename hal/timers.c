#include "timers.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint32_t milliseconds_passed = 0;
static volatile uint16_t cycles_left = 0;
static volatile bool emitting = false;

void timers_init(void)
{
    // Timer0 for meander.
    TCCR0A = _BV(COM0A0) | _BV(WGM01);  // Toggle channel A, CTC mode.
    DDRD |= _BV(PD6);

    // Timer2 for milliseconds.
    TCCR2A = _BV(WGM21);  // CTC mode
    TCCR2B = _BV(CS22) | _BV(CS20);  // prescaler 128
    OCR2A = 124;
    TIMSK2 = _BV(OCIE2A);
}

ISR(TIMER2_COMPA_vect)
{
    milliseconds_passed++;
}

uint32_t ms_passed(void)
{
    TIMSK2 = 0;
    uint32_t ms = milliseconds_passed;
    TIMSK2 = _BV(OCIE2A);
    return ms;
}

void ms_wait(uint32_t ms)
{
    uint32_t now = ms_passed();
    while (ms_passed() - now < ms) {}
}

void meander_start(uint16_t freq)
{
    if (meander_emitting())
        meander_stop();
    /* freq = F_CPU / (2 * presc * (regvalue + 1))
     * 
     * So we need to choose the prescaler value so that regvalue 
     * will be in between 0 and 255.
     */
    const uint16_t presc_shifts[5] = {0, 3, 6, 8, 10};
    const uint32_t product = F_CPU / ((uint32_t)freq << 1);
    uint32_t regvalue;
    uint8_t i;

    for (i = 0; i < 5; i++) {
        regvalue = (product >> presc_shifts[i]) - 1;
        if (regvalue < 256) {
            break;
        }
    }
    TCCR0B = i + 1;  // corresponding bit mask (0b1..0b101)
    OCR0A = (uint8_t)regvalue;
    emitting = true;
}

void meander_stop(void)
{
    TCCR0B = 0;
    TIMSK0 = 0;
    cycles_left = 0;
    PORTD &= ~_BV(PD6);
    emitting = false;
}

void meander_emit(uint16_t freq, uint16_t duration)
{
    meander_start(freq);

    /* Meander period is 2 cycles (on each interrupt output pin is toggled).
     * So the formuls for cycles left will be:
     *      (2 * freq(Hz)) * duration(ms) / 1000 (ms)
     */
    cycles_left = (uint32_t)freq * duration / 500;
    TIMSK0 = _BV(OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
    if (!cycles_left--) {
        meander_stop();
    }
}

bool meander_emitting(void)
{
    return emitting;
}
