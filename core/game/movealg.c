#include <config.h>
#include "movealg.h"
#include "randnum.h"
#include "routes.h"

static void start_drawings_route(struct paranormal_entity *e)
{
    uint8_t spawn_slots[4] = {DRAWING_R1L, DRAWING_R1R, DRAWING_R3L, DRAWING_R3R};
    uint8_t free_slots_num, slot_id;

    free_slots_num = slots_filter_free(SLOT_DRAWING, spawn_slots, 4);
    slot_id = spawn_slots[randidx(free_slots_num)];

    switch (slot_id) {
        case DRAWING_R1L:
        case DRAWING_R3R:
            if (randidx(2))
                e->route = ROUTE_1L_L;
            else
                e->route = ROUTE_3R_R;
            break;
        
        case DRAWING_R1R:
            e->route = ROUTE_1R_L;
            break;
        
        case DRAWING_R3L:
            e->route = ROUTE_3L_R;
            break;
    }

    slot_occupy(e, SLOT_DRAWING, slot_id);
}

static bool possess_closest_lamp(struct paranormal_entity *e)
{
    enum room_light rls[2];
    find_closest_lamps(e->slot_id, rls);
    uint8_t nfree = slots_filter_free(SLOT_LAMP, rls, 2);

    if (nfree) {
        slot_occupy(e, SLOT_LAMP, rls[randidx(nfree)]);
        return true;
    }
    return false;
}

static void possess_random_lamp_or_tv(struct paranormal_entity *e)
{
    enum room_light rls[NUM_OF_ROOM_LIGHTS] = {
        RL_R3_DESK,
        RL_R4_FLOOR,
        RL_R6_DESK,
        RL_R6_FLOOR,
        RL_R7_DESK,
        RL_R7_FLOOR,
    };
    uint8_t nfree = slots_filter_free(SLOT_LAMP, rls, NUM_OF_ROOM_LIGHTS);
    uint8_t slot_id = 0;

    if (slots_filter_free(SLOT_TV, &slot_id, 1))
        nfree++;
    
    slot_id = randidx(nfree);

    if (slot_id < NUM_OF_ROOM_LIGHTS)
        slot_occupy(e, SLOT_LAMP, slot_id);
    else
        slot_occupy(e, SLOT_TV, 0);
}

static void possess_random_cam(struct paranormal_entity *e)
{
    enum camera_light cams[NUM_OF_CAMS - 1] = 
        {CAM_L1, CAM_L2, CAM_L3, CAM_L4, CAM_L5, CAM_L6, CAM_L7};
    uint8_t nfree = slots_filter_free(SLOT_CAM, cams, NUM_OF_CAMS - 1);

    slot_occupy(e, SLOT_CAM, cams[randidx(NUM_OF_CAMS - 1)]);
}

static void move_to_next_drawing(struct paranormal_entity *e)
{
    enum drawing next_drawing = read_next_drawing(e->route, e->slot_id);
    slot_occupy(e, SLOT_DRAWING, next_drawing);
}

static void exorcise_from_lamp_to_drawing(struct paranormal_entity *e)
{
    enum drawing drs[3];
    find_drawings_nearby(e->slot_id, drs);
    uint8_t nfree = slots_filter_free(SLOT_DRAWING, drs, 3);
    slot_occupy(e, SLOT_DRAWING, drs[randidx(3)]);
}

void movealg_classic(void *arg)
{
    struct paranormal_entity *e = arg;

    if (e->activity_lvl >= randnum(MAX_ACTIVITY_LVL)) { 
        switch (e->slot_type) {
            case SLOT_NONE:
                start_drawings_route(e);
                break;

            case SLOT_DRAWING:
                if (e->possessivility_lvl >= randnum(MAX_POSSESSIVILITY_LVL)) {
                    if (possess_closest_lamp(e))
                        break;
                }
                move_to_next_drawing(e);
                break;
            
            case SLOT_LAMP:
                exorcise_from_lamp_to_drawing(e);
            
            default: break;
        }
    }
}

void movealg_simplified(void *arg)
{
    struct paranormal_entity *e = arg;

    if (e->activity_lvl >= randnum(MAX_ACTIVITY_LVL)) { 
        switch (e->slot_type) {
            case SLOT_NONE:
                start_drawings_route(e);
                break;

            case SLOT_DRAWING:
                move_to_next_drawing(e);
                break;
            
            default: break;
        }
    }
}

void movealg_quickly(void *arg)
{
    struct paranormal_entity *e = arg;
    struct alg_quick_arg *alg_data = e->alg_data;

    if (e->slot_type == SLOT_DRAWING && alg_data->stage >= QUICK_MOVEALG_PREPARE_STAGES) {
        move_to_next_drawing(e);
    } else if (e->activity_lvl >= randnum(MAX_ACTIVITY_LVL)) {
        if (e->slot_type == SLOT_NONE) { 
            start_drawings_route(e);
            alg_data->tmev->timeout = ACTION_PERIOD_RED;
            alg_data->stage = 0;
        } else if (e->slot_type == SLOT_DRAWING) {
            alg_data->stage++;
            if (alg_data->stage >= QUICK_MOVEALG_PREPARE_STAGES)
                alg_data->tmev->timeout = QUICK_MOVEALG_ACTION_PERIOD;
        }
    }
}

void movealg_pltlamp(void *arg)
{
    struct paranormal_entity *e = arg;

    if (e->activity_lvl >= randnum(MAX_ACTIVITY_LVL) && e->slot_type == SLOT_NONE) {
        possess_random_lamp_or_tv(e);
    }
}

void movealg_pltcam(void *arg)
{
    struct paranormal_entity *e = arg;

    if (e->activity_lvl >= randnum(MAX_ACTIVITY_LVL) && e->slot_type == SLOT_NONE) {
        possess_random_cam(e);
    }
}
