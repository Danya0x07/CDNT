#include "view.h"
#include <string.h>
#include <house.h>
#include <graphics.h>
#include <txt.h>
#include <img.h>
#include "slots.h"
#include "entities.h"
#include "components.h"
#include "camera.h"
#include "ceilings.h"
#include "flashes.h"
#include "clock.h"
#include "score.h"
#include "pwr.h"

struct screen_data {
    // Room independent
    uint8_t hour;
    uint8_t score;
    uint8_t consumption;
    bool firstupd;

    // Room dependent
    enum camera cam;
    bool cam_possessed;
    bool cam_uv;
    bool opt_statuses[3];
};

static struct screen_data scd, last_scd;
static const struct screen_data default_scd = {
    .hour = 0, .score = 0, .consumption = 1, .firstupd = false, 
    .cam = CAMP, .cam_possessed = false, .cam_uv = false, .opt_statuses = {0}
};

void view_reset_screen(void)
{
    memcpy(&scd, &default_scd, sizeof(struct screen_data));
    memcpy(&last_scd, &default_scd, sizeof(struct screen_data));
}

void view_init_screen(void)
{
    gfx_set_scale(GFX_SCALE_X2);
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_clear();
    gfx_print_txt_f(76, 0, txt_hours);
    gfx_draw_image(100, 73, &img_joystick);

    gfx_set_scale(GFX_SCALE_X1);
    gfx_print_txt_f(112, 24, txt_attacks);
    gfx_draw_frame(0, 32, 12, 96, 2);
    gfx_draw_rect(3, 28, 6, 4);

    scd.firstupd = false;
}

static void redraw_hour(void)
{
    uint8_t x = 147;

    if (scd.hour > 9)  // What if?
        x -= 12;
    
    gfx_set_scale(GFX_SCALE_X2);
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_print_dec(x, 0, scd.hour);
    last_scd.hour = scd.hour;
}

static void redraw_score(void)
{
    uint8_t x = 153;

    if (scd.score > 9)
        x -= 6;
    if (scd.score > 99)
        x -= 6;
    
    gfx_set_scale(GFX_SCALE_X1);
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_print_dec(x, 24, scd.score);
    last_scd.score = scd.score;
}

static void redraw_consumption(void)
{
    static const enum gfx_color colors[PWR_CONSUMPTION_MAX] = {
        GFX_COLOR_CYAN,
        GFX_COLOR_GREEN,
        GFX_COLOR_GREEN,
        GFX_COLOR_YELLOW,
        GFX_COLOR_RED,
        GFX_COLOR_RED
    };
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_clear_rect(3, 34, 6, 90);
    for (uint8_t i = 0; i < scd.consumption; i++) {
        gfx_set_color(colors[i], GFX_COLOR_BLACK);
        gfx_draw_rect(3, 111 - 15 * i, 6, 14);
    }
    last_scd.consumption = scd.consumption;
}

static void redraw_cam_no(void)
{
    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X2);
    gfx_clear_rect(0, 0, 48, 16);
    if (scd.cam == CAMP) {
        gfx_print_ch(0, 0, '-');
    } else {
        gfx_set_color(scd.cam_uv ? GFX_COLOR_MAGENTA : GFX_COLOR_WHITE, GFX_COLOR_BLACK);
        if (scd.cam_possessed)
            gfx_set_color(GFX_COLOR_RED, GFX_COLOR_BLACK);
        gfx_print_txt_f(0, 0, txt_cam);
        gfx_print_dec(36, 0, scd.cam + 1);
    }
    last_scd.cam = scd.cam;
    last_scd.cam_uv = scd.cam_uv;
    last_scd.cam_possessed = scd.cam_possessed;
}

static void redraw_room_options(void)
{
    static const struct gfx_image *opt_imgs[NUM_OF_CAMS][2] = {
        [CAM1] = {&img_noopt, &img_noopt},
        [CAM2] = {&img_noopt, &img_noopt},
        [CAM3] = {&img_desklamp, &img_tv},
        [CAM4] = {&img_noopt, &img_floorlamp},
        [CAM5] = {&img_noopt, &img_noopt},
        [CAM6] = {&img_desklamp, &img_floorlamp},
        [CAM7] = {&img_desklamp, &img_desklamp},
        [CAMP] = {&img_flash, &img_flash}
    };
    static const enum gfx_color opt_active_colors[NUM_OF_CAMS][2] = {
        [CAM1] = {GFX_COLOR_BLACK, GFX_COLOR_BLACK},
        [CAM2] = {GFX_COLOR_BLACK, GFX_COLOR_BLACK},
        [CAM3] = {GFX_COLOR_YELLOW, GFX_COLOR_CYAN},
        [CAM4] = {GFX_COLOR_BLACK, GFX_COLOR_YELLOW},
        [CAM5] = {GFX_COLOR_BLACK, GFX_COLOR_BLACK},
        [CAM6] = {GFX_COLOR_YELLOW, GFX_COLOR_YELLOW},
        [CAM7] = {GFX_COLOR_YELLOW, GFX_COLOR_YELLOW},
        [CAMP] = {GFX_COLOR_YELLOW, GFX_COLOR_YELLOW}
    };
    
    gfx_set_scale(GFX_SCALE_X1);

    gfx_set_color(GFX_COLOR_WHITE, GFX_COLOR_BLACK);
    if (scd.cam == CAMP) {
        gfx_draw_image(108, 63, &img_pause);
        gfx_set_color(scd.opt_statuses[2] ? GFX_COLOR_MAGENTA : GFX_COLOR_BLUE, GFX_COLOR_BLACK);
        gfx_draw_image(108, 109, &img_autoflash);
    } else {
        gfx_draw_image(108, 63, &img_closecam);
        gfx_set_color(scd.opt_statuses[2] ? GFX_COLOR_YELLOW : GFX_COLOR_WHITE, GFX_COLOR_BLACK);
        gfx_draw_image(108, 109, &img_ceiling);
    }
    
    gfx_clear_rect(80, 86, 18, 8);
    gfx_clear_rect(136, 86, 18, 8);
    if (scd.cam_possessed == false) {
        gfx_set_color(scd.opt_statuses[0] ? opt_active_colors[scd.cam][0] : GFX_COLOR_WHITE, GFX_COLOR_BLACK);
        gfx_draw_image(80, 86, opt_imgs[scd.cam][0]);
        gfx_set_color(scd.opt_statuses[1] ? opt_active_colors[scd.cam][1] : GFX_COLOR_WHITE, GFX_COLOR_BLACK);
        gfx_draw_image(136, 86, opt_imgs[scd.cam][1]);
    }
    memcpy(last_scd.opt_statuses, scd.opt_statuses, sizeof(scd.opt_statuses));
    last_scd.cam_possessed = scd.cam_possessed;
}

void view_update_screen(void)
{
    scd.hour = clock_get();
    scd.score = score_get();
    scd.consumption = pwr_consumption_exceeds() ? PWR_CONSUMPTION_MAX : pwr_consumption_get();
    scd.cam = camera_get_no();
    scd.cam_uv = camera_get_mode() == CAM_MODE_UV;
    scd.cam_possessed = !slot_is_free(SLOT_CAM, scd.cam);

    switch (scd.cam) {
        case CAM3:
            scd.opt_statuses[0] = !slot_is_free(SLOT_LAMP, RL_R3_DESK);
            scd.opt_statuses[1] = !slot_is_free(SLOT_TV, 0);
            break;
        
        case CAM4:
            scd.opt_statuses[1] = !slot_is_free(SLOT_LAMP, RL_R4_FLOOR);
            break;
        
        case CAM6:
            scd.opt_statuses[0] = !slot_is_free(SLOT_LAMP, RL_R6_DESK);
            scd.opt_statuses[1] = !slot_is_free(SLOT_LAMP, RL_R6_FLOOR);
            break;
        
        case CAM7:
            scd.opt_statuses[0] = !slot_is_free(SLOT_LAMP, RL_R7_DESK);
            scd.opt_statuses[1] = !slot_is_free(SLOT_LAMP, RL_R7_FLOOR);
            break;
        
        case CAMP:
            scd.opt_statuses[0] = flash_get(FLASH_L) == FLASH_MODE_W;
            scd.opt_statuses[1] = flash_get(FLASH_R) == FLASH_MODE_W;
            break;
        
        default:
            scd.opt_statuses[0] = false;
            scd.opt_statuses[1] = false;
    }
    if (scd.cam != CAMP)
        scd.opt_statuses[2] = ceiling_get(scd.cam);
    else
        scd.opt_statuses[2] = flash_get(FLASH_L) == FLASH_MODE_UV || flash_get(FLASH_R) == FLASH_MODE_UV;
    
    if (!scd.firstupd) {
        redraw_hour();
        redraw_score();
        redraw_consumption();
        redraw_cam_no();
        redraw_room_options();
        scd.firstupd = true;
    }
    if (scd.hour != last_scd.hour)
        redraw_hour();
    if (scd.score != last_scd.score)
        redraw_score();
    if (scd.consumption != last_scd.consumption)
        redraw_consumption();
    if (scd.cam != last_scd.cam || scd.cam_possessed != last_scd.cam_possessed) {
        redraw_cam_no();
        redraw_room_options();
    }
    if (scd.cam_uv != last_scd.cam_uv)
        redraw_cam_no();
    if (memcmp(scd.opt_statuses, last_scd.opt_statuses, sizeof(scd.opt_statuses)))
        redraw_room_options();
}

void view_show_nopower(void)
{
    gfx_set_color(GFX_COLOR_RED, GFX_COLOR_BLACK);
    gfx_set_scale(GFX_SCALE_X3);
    gfx_clear();
    gfx_print_txt_f(0, 0, txt_nopower);
}

static bool uv_entity_uncover_without_cam(enum drawing d)
{
    bool uncovered = d == DRAWING_RPM;
    d |= (d == DRAWING_RPL && flash_get(FLASH_L) == FLASH_MODE_UV);
    d |= (d == DRAWING_RPR && flash_get(FLASH_R) == FLASH_MODE_UV);
    return uncovered;
}

void view_update_lights(void)
{
    entity_id e;
    
    for (enum drawing d = DRAWING_R1L; d < NUM_OF_DRAWINGS; d++) {
        if ((e = slot_get_occupier(SLOT_DRAWING, d)) != NO_ENTITY) {
            struct cpn_view *view = component_get(e, COMPONENT_VIEW);

            if (view) {
                if (view->visibility == VISIBILITY_W) {
                    drawing_light_set(d, view->color);
                } else if (view->visibility == VISIBILITY_UV) {
                    if (camera_get_mode() == CAM_MODE_UV || uv_entity_uncover_without_cam(d)) {
                        drawing_light_set(d, view->color);
                    } else {
                        drawing_light_set(d, DCOLOR_OFF);
                    }       
                }
            }
        } else {
            drawing_light_set(d, DCOLOR_OFF);
        }
    }

    for (enum room_lamp l = _RL_FIRST; l < NUM_OF_ROOM_LAMPS; l++) {
        lamp_light_set(l, !slot_is_free(SLOT_LAMP, l));
    }

    for (enum ceiling c = _CEILING_FIRST; c < NUM_OF_CEILINGS; c++) {
        ceiling_light_set(c, ceiling_get(c));
    }

    tv_noise_set(!slot_is_free(SLOT_TV, 0));

    flash_light_set(FLASH_L, flash_get(FLASH_L));
    flash_light_set(FLASH_R, flash_get(FLASH_R));

    for (enum camera cam = CAM1; cam < NUM_OF_CAMS; cam++) {
        if (camera_get_no() == cam)
            camera_light_set(cam, camera_get_mode());
        else
            camera_light_set(cam, CAM_MODE_OFF);
    }

    enum camera cam = camera_get_no();
    if (slot_is_free(SLOT_CAM, cam)) {
        room_mask_set(1 << cam);
    } else {
        room_mask_set(0);
    }

    if (!slot_is_free(SLOT_DRAWING, DRAWING_RPM)) {
        room_mask_set(MASK_ROOMP);
    }

    house_update();
}