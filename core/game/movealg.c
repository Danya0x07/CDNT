#include <config.h>
#include <house.h>
#include "movealg.h"
#include "entities.h"
#include "components.h"
#include "actions.h"
#include "randnum.h"

static void start_drawings_route(entity_id entity)
{
    uint8_t spawn_slots[4] = {DRAWING_R1L, DRAWING_R1R, DRAWING_R3L, DRAWING_R3R};
    struct cpn_route *route = component_get(entity, COMPONENT_ROUTE);
    uint8_t free_slots_num, slot_idx;

    free_slots_num = slots_filter_free(SLOT_DRAWING, spawn_slots, 4);
    slot_idx = spawn_slots[randidx(free_slots_num)];

    switch (slot_idx) {
        case DRAWING_R1L:
        case DRAWING_R3R:
            if (randidx(2))
                route->variant = ROUTEVAR_1L_L;
            else
                route->variant = ROUTEVAR_3R_R;
            break;
        
        case DRAWING_R1R:
            route->variant = ROUTEVAR_1R_L;
            break;
        
        case DRAWING_R3L:
            route->variant = ROUTEVAR_3L_R;
            break;
    }

    slot_occupy(entity, SLOT_DRAWING, slot_idx);
}

static bool possess_closest_lamp(entity_id entity)
{
    struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);
    enum room_light rls[2];

    find_closest_lamps(slot->idx, rls);
    uint8_t nfree = slots_filter_free(SLOT_LAMP, rls, 2);

    if (nfree) {
        slot_occupy(entity, SLOT_LAMP, rls[randidx(nfree)]);
        return true;
    }
    return false;
}

static void possess_random_lamp_or_tv(entity_id entity)
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
    uint8_t slot_idx = 0;

    if (slots_filter_free(SLOT_TV, &slot_idx, 1))
        nfree++;
    
    slot_idx = randidx(nfree);

    if (slot_idx < NUM_OF_ROOM_LIGHTS)
        slot_occupy(entity, SLOT_LAMP, slot_idx);
    else
        slot_occupy(entity, SLOT_TV, 0);
}

static void possess_random_cam(entity_id entity)
{
    enum camera_light cams[NUM_OF_CAMS - 1] = 
        {CAM_L1, CAM_L2, CAM_L3, CAM_L4, CAM_L5, CAM_L6, CAM_L7};
    uint8_t nfree = slots_filter_free(SLOT_CAM, cams, NUM_OF_CAMS - 1);

    slot_occupy(entity, SLOT_CAM, cams[randidx(nfree)]);
}

static void move_to_next_drawing(entity_id entity)
{
    struct cpn_route *route = component_get(entity, COMPONENT_ROUTE);
    struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);
    enum drawing next_drawing = route_read_next(route->variant, slot->idx);
    slot_occupy(entity, SLOT_DRAWING, next_drawing);
}

static void exorcise_from_lamp_to_drawing(entity_id entity)
{
    struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);
    enum drawing drs[3];
    find_drawings_nearby(slot->idx, drs);
    uint8_t nfree = slots_filter_free(SLOT_DRAWING, drs, 3);
    slot_occupy(entity, SLOT_DRAWING, drs[randidx(nfree)]);
}

void movealg_classic(entity_id entity)
{
    struct cpn_activity *activity = component_get(entity, COMPONENT_ACTIVITY);

    if (activity->lvl >= randnum(MAX_ACTIVITY_LVL)) { 
        struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);
        struct cpn_possessivity *possessivity = component_get(entity, COMPONENT_POSSESSIVITY);

        switch (slot->type) {
            case SLOT_NONE:
                start_drawings_route(entity);
                break;

            case SLOT_DRAWING:
                if (possessivity->lvl >= randnum(MAX_POSSESSIVILITY_LVL)) {
                    if (possess_closest_lamp(entity))
                        break;
                }
                move_to_next_drawing(entity);
                break;
            
            case SLOT_LAMP:
                exorcise_from_lamp_to_drawing(entity);
            
            default: break;
        }
    }
}

void movealg_simplified(entity_id entity)
{
    struct cpn_activity *activity = component_get(entity, COMPONENT_ACTIVITY);

    if (activity->lvl >= randnum(MAX_ACTIVITY_LVL)) {
        struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);

        switch (slot->type) {
            case SLOT_NONE:
                start_drawings_route(entity);
                break;

            case SLOT_DRAWING:
                move_to_next_drawing(entity);
                break;
            
            default: break;
        }
    }
}

void movealg_quick(entity_id entity, uint32_t *act_timeout)
{
    struct cpn_activity *activity = component_get(entity, COMPONENT_ACTIVITY);
    struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);
    struct cpn_readiness *readiness = component_get(entity, COMPONENT_READINESS);

    if (slot->type == SLOT_DRAWING && readiness->degree >= NUM_OF_QUICK_MOVE_PREPARE_DEGREES) {
        move_to_next_drawing(entity);
    } else if (activity->lvl >= randnum(MAX_ACTIVITY_LVL)) {
        if (slot->type == SLOT_NONE) { 
            start_drawings_route(entity);
            *act_timeout = ACTION_TIMEOUT_RED;
            readiness->degree = 0;
        } else if (slot->type == SLOT_DRAWING) {
            readiness->degree++;
            if (readiness->degree >= NUM_OF_QUICK_MOVE_PREPARE_DEGREES)
                *act_timeout = ACTION_TIMEOUT_QUICK;
        }
    }
}

void movealg_pltlamp(entity_id entity)
{
    struct cpn_activity *activity = component_get(entity, COMPONENT_ACTIVITY);
    struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);

    if (activity->lvl >= randnum(MAX_ACTIVITY_LVL) && slot->type == SLOT_NONE) {
        possess_random_lamp_or_tv(entity);
    }
}

void movealg_pltcam(entity_id entity)
{
    struct cpn_activity *activity = component_get(entity, COMPONENT_ACTIVITY);
    struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);

    if (activity->lvl >= randnum(MAX_ACTIVITY_LVL) && slot->type == SLOT_NONE) {
        possess_random_cam(entity);
    }
}
