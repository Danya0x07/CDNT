#include <game.h>
#include <config.h>
#include <music.h>
#include <tracks.h>

#include "player.h"
#include "entities.h"
#include "slots.h"
#include "flashes.h"
#include "ceilings.h"
#include "camera.h"
#include "moves.h"
#include "setup.h"
#include "view.h"
#include "score.h"
#include "pwr.h"
#include "clock.h"

static bool pause_requested = false;
static uint8_t night_no;

static bool night_completed(void);
static bool night_failed(void);
static void check_kicked_cam_possessors(void);
static void check_power_consumption(uint32_t t);
static void handle_player_request(struct player_request request, uint32_t t);
static void check_timeout_events(uint32_t t);
static bool powered(void);

bool game_is_active(void)
{
    return !pause_requested && !night_completed() && !night_failed();
}

void game_enter(struct game_input *params)
{
    if (params->request == GR_NEW_GAME) {
        setup_entities(params->night_no);
        house_reset();
        score_reset();
        ceilings_off();
        flashes_reset();
        clock_reset();
        camera_select(CAMP);
        view_reset_screen();
        night_no = params->night_no;
    }
    
    timeout_event_init(&tmev_yellow_move, params->moment);
    timeout_event_init(&tmev_blue_move, params->moment);
    timeout_event_init(&tmev_red_move, params->moment);
    timeout_event_init(&tmev_pltlamp_move, params->moment);
    timeout_event_init(&tmev_pltcam_move, params->moment);
    timeout_event_init(&tmev_clock, params->moment);

    pwr_init();
    view_init_screen();

    pause_requested = false;
}

void game_tick(enum joystick_event jev, uint8_t btnev, uint32_t t)
{
    struct player_request request = request_get(jev, btnev, camera_get_no());

    if (powered())
        handle_player_request(request, t);

    check_timeout_events(t);
    check_kicked_cam_possessors();
    check_power_consumption(t);

    if (powered()) {
        view_update_screen();
        view_update_lights();
    }
}

void game_get_results(struct game_output *results)
{
    if (pause_requested) {
        results->status = GS_PAUSE;
    } else if (night_completed()) {
        results->status = GS_NIGHT_COMPLETED;
    } else {
        results->status = GS_NIGHT_FAILED;
    }
    results->night_no = night_no;
    results->hour = clock_get();
    results->score = score_get();
}

static bool night_completed(void)
{
    return clock_get() == NUM_OF_HOURS;
}

static bool night_failed(void)
{
    return !slot_is_free(SLOT_DRAWING, DRAWING_RPM);
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

static void check_power_consumption(uint32_t t)
{
    pwr_update();
    
    if (pwr_consumption_exceeds() && !tmev_pwr_kill.active) {
        timeout_event_init(&tmev_pwr_kill, t);
    }

    if (pwr_status_get() == PWR_OFF && !tmev_pwr_restore.active) {
        timeout_event_init(&tmev_pwr_restore, t);
    }
}

static void handle_player_request(struct player_request request, uint32_t t)
{
    switch (request.type) {
        case PR_NOTHING: break;
        case PR_WFLASH_L:
            if (flash_shoot(FLASH_L, FLASH_MODE_W)) {
                timeout_event_init(&tmev_flash_off, t);
                timeout_event_init(&tmev_lflash_recharge, t);
                music_start(&track_flash);
            }
            break;

        case PR_WFLASH_R:
            if (flash_shoot(FLASH_R, FLASH_MODE_W)) {
                timeout_event_init(&tmev_flash_off, t);
                timeout_event_init(&tmev_rflash_recharge, t);
                music_start(&track_flash);
            }
            break;
        
        case PR_UVFLASH:
            {
                enum flash flash = get_flash_for_uv_entity();
                if (flash_shoot(flash, FLASH_MODE_UV)) {
                    timeout_event_init(&tmev_flash_off, t);
                    timeout_event_init(flash == FLASH_L ? 
                        &tmev_lflash_recharge : &tmev_rflash_recharge, t);
                    music_start(&track_flash);
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
                    music_start(&track_lamp_off);
                }
            }
            break;
        
        case PR_TV_OFF:
            {
                entity_id entity = slot_get_occupier(SLOT_TV, 0);
                if (entity) {
                    entity_kick_away(entity);
                    music_start(&track_lamp_off);
                }
            }
            break;
        
        case PR_SELECT_CAM:
            camera_select(request.cam);
            if (slot_is_free(SLOT_CAM, request.cam))
                music_start(&track_cam_switch);
            else
                music_start(&track_cam_nosignal);
            break;
        
        case PR_UV_ON:
            camera_enable_uv();
            if (slot_is_free(SLOT_CAM, camera_get_no()))
                music_start(&track_cam_uv_switch);
            else
                music_start(&track_cam_nosignal);
            break;
        
        case PR_UV_OFF:
            camera_disable_uv();
            if (slot_is_free(SLOT_CAM, camera_get_no()))
                music_start(&track_cam_uv_switch);
            else
                music_start(&track_cam_nosignal);
            break;
        
        case PR_PAUSE:
            pause_requested = true;
            music_start(&track_pause);
            break;
    }
}

static void check_timeout_events(uint32_t t)
{
    timeout_event_check(&tmev_flash_off, t);
    timeout_event_check(&tmev_lflash_recharge, t);
    timeout_event_check(&tmev_rflash_recharge, t);

    timeout_event_check(&tmev_clock, t);

    timeout_event_check(&tmev_red_move, t);
    timeout_event_check(&tmev_yellow_move, t);
    timeout_event_check(&tmev_blue_move, t);
    timeout_event_check(&tmev_pltlamp_move, t);
    timeout_event_check(&tmev_pltcam_move, t);

    timeout_event_check(&tmev_pwr_kill, t);
    timeout_event_check(&tmev_pwr_restore, t);
}

static bool powered(void)
{
    return pwr_status_get() == PWR_ON;
}