#include <game.h>
#include <config.h>
#include "player.h"
#include "entities.h"
#include "slots.h"
#include "flashes.h"
#include "ceilings.h"
#include "camera.h"
#include "moves.h"
#include "setup.h"
#include "view.h"

uint8_t __hour = 12;
uint8_t __pwr_consumption = 0;
uint8_t __score = 0;

static void check_kicked_cam_possessors(void);

bool game_is_active(void)
{
    return slot_is_free(SLOT_DRAWING, DRAWING_RPM);
}

void game_enter(struct game_input *params)
{
    if (params->request == GR_NEW_GAME) {
        house_reset();
        setup_entities(params->night_no);
        ceilings_off();
        flashes_reset();
        camera_select(CAMP);
    }
    
    timeout_event_init(&tmev_yellow_move, params->moment);
    timeout_event_init(&tmev_blue_move, params->moment);
    timeout_event_init(&tmev_red_move, params->moment);
    timeout_event_init(&tmev_pltlamp_move, params->moment);
    timeout_event_init(&tmev_pltcam_move, params->moment);
}

void game_tick(enum joystick_event jev, uint8_t btnev, uint32_t t)
{
    // Process user events
    struct player_request request = request_get(jev, btnev, camera_get_no());

    switch (request.type) {
        case PR_NOTHING: break;
        case PR_WFLASH_L:
            if (flash_shoot(FLASH_L, FLASH_MODE_W)) {
                timeout_event_init(&tmev_flash_off, t);
                timeout_event_init(&tmev_lflash_recharge, t);
            }
            break;

        case PR_WFLASH_R:
            if (flash_shoot(FLASH_R, FLASH_MODE_W)) {
                timeout_event_init(&tmev_flash_off, t);
                timeout_event_init(&tmev_rflash_recharge, t);
            }
            break;
        
        case PR_UVFLASH:
            {
                enum flash flash = get_flash_for_uv_entity();
                if (flash_shoot(flash, FLASH_MODE_UV)) {
                    timeout_event_init(&tmev_flash_off, t);
                    timeout_event_init(flash == FLASH_L ? 
                        &tmev_lflash_recharge : &tmev_rflash_recharge, t);
                }
            }
            break;
        
        case PR_CEILING_TG:
            ceiling_toggle(request.ceiling);
            break;
        
        case PR_LAMP_OFF:
            {
                entity_id entity = slot_get_occupier(SLOT_LAMP, request.lamp);
                if (entity) {
                    entity_kick_away(entity);
                }
            }
            break;
        
        case PR_TV_OFF:
            {
                entity_id entity = slot_get_occupier(SLOT_TV, 0);
                if (entity) {
                    entity_kick_away(entity);
                }
            }
            break;
        
        case PR_SELECT_CAM:
            camera_select(request.cam);
            break;
        
        case PR_UV_ON:
            camera_enable_uv();
            break;
        
        case PR_UV_OFF:
            camera_disable_uv();
            break;
        
        case PR_PAUSE:
            break;
    }

    // Proces time-dependent events
    timeout_event_check(&tmev_flash_off, t);
    timeout_event_check(&tmev_lflash_recharge, t);
    timeout_event_check(&tmev_rflash_recharge, t);

    timeout_event_check(&tmev_red_move, t);
    timeout_event_check(&tmev_yellow_move, t);
    timeout_event_check(&tmev_blue_move, t);
    timeout_event_check(&tmev_pltlamp_move, t);
    timeout_event_check(&tmev_pltcam_move, t);

    // Process game data
    check_kicked_cam_possessors();

    // Update view
    view_update_lights();
}

void game_get_results(struct game_output *results)
{
    
}

static void check_kicked_cam_possessors(void)
{
    for (enum ceiling c = CEILING1; c < NUM_OF_CEILINGS; c++) {
        if (ceiling_get(c)) {
            entity_id entity = slot_get_occupier(SLOT_CAM, (enum camera)c);
            if (entity) {
                entity_kick_away(entity);
            }
        }
    }
}
