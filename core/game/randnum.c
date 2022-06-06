#include "randnum.h"
#include <stdlib.h>

uint8_t randidx(uint8_t n)
{
    return rand() % n;
}

uint8_t randnum(uint8_t max)
{
    return randidx(max) + 1;
}