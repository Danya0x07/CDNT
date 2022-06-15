#include "entities.h"
#include "components.h"
#include "movealg.h"

void entity_setup(entity_id entity, uint8_t activity_lvl)
{
    struct cpn_activity *activity = component_get(entity, COMPONENT_ACTIVITY);

    activity->lvl = activity_lvl;
    movealg_reset_route(entity);
}

void entity_move(entity_id entity, void *arg)
{    
    switch (entity) {
        case ENTITY_YELLOW:
            movealg_classic_move(ENTITY_YELLOW);
            break;
        
        case ENTITY_UV:
            movealg_simplified_move(ENTITY_UV);
            break;
        
        case ENTITY_RED:
            movealg_quick_move(ENTITY_RED, arg);
            break;
        
        case ENTITY_PLTLAMP:
            movealg_static_move(ENTITY_PLTLAMP, PT_LAMP_TV);
            break;
        
        case ENTITY_PLTCAM:
            movealg_static_move(ENTITY_PLTCAM, PT_CAM);
            break;
        
        default:
            break;
    }
}

void entity_kick_away(entity_id entity)
{
    struct cpn_slot *slot = component_get(entity, COMPONENT_SLOT);
    
    switch (entity) {
        case ENTITY_YELLOW:
        case ENTITY_UV:
        case ENTITY_RED:
            if (slot->type == SLOT_LAMP) {
                movealg_exorcise_from_lamp_to_drawing(entity);
            } else {
                movealg_reset_route(entity);
            }
            break;
        
        case ENTITY_PLTLAMP:
        case ENTITY_PLTCAM:
            movealg_reset_route(entity);
            break;
        
        default:
            break;
    }
}