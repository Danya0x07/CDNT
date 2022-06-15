#include <stddef.h>
#include <config.h>

#include "moves.h"
#include "entities.h"

static void yellow_move_cb(void);
static void red_move_cb(void);
static void blue_move_cb(void);
static void pltlamp_move_cb(void);
static void pltcam_move_cb(void);

struct timeout_event tmev_yellow_move = {
    .timeout = ACTION_TIMEOUT_YELLOW,
    .callback = yellow_move_cb,
    .active = true,
    .periodic = true
};

struct timeout_event tmev_red_move = {
    .timeout = ACTION_TIMEOUT_RED,
    .callback = red_move_cb,
    .active = true,
    .periodic = true
};

struct timeout_event tmev_blue_move = {
    .timeout = ACTION_TIMEOUT_BLUE,
    .callback = blue_move_cb,
    .active = true,
    .periodic = true
};

struct timeout_event tmev_pltlamp_move = {
    .timeout = ACTION_TIMEOUT_PLTLAMP,
    .callback = pltlamp_move_cb,
    .active = true,
    .periodic = true
};

struct timeout_event tmev_pltcam_move = {
    .timeout = ACTION_TIMEOUT_PLTCAM,
    .callback = pltcam_move_cb,
    .active = true,
    .periodic = true
};

static void yellow_move_cb(void)
{
    entity_move(ENTITY_YELLOW, NULL);
}

static void red_move_cb(void)
{
    entity_move(ENTITY_RED, &tmev_red_move.timeout);
}

static void blue_move_cb(void)
{
    entity_move(ENTITY_UV, NULL);
}

static void pltlamp_move_cb(void)
{
    entity_move(ENTITY_PLTLAMP, NULL);
}

static void pltcam_move_cb(void)
{
    entity_move(ENTITY_PLTCAM, NULL);
}
