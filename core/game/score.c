#include "score.h"

static uint16_t score;

void score_reset(void)
{
    score = 0;
}

void score_add(uint8_t points)
{
    score += points;
}

uint16_t score_get(void)
{
    return score;
}