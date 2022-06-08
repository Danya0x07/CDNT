#include "view.h"
#include <house.h>
#include "slots.h"
#include "entities.h"
#include "components.h"
#include "camera.h"
#include "ceilings.h"
#include "flashes.h"

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

    enum camera_no cam;

    for (cam = CAM1; cam < NUM_OF_CAMS; cam++) {
        if (camera_get_no() == cam)
            camera_light_set(cam, camera_get_mode());
        else
            camera_light_set(cam, CAM_MODE_OFF);
    }
    cam = camera_get_no();
    room_mask_set((1 << cam) * slot_is_free(SLOT_CAM, cam));

    house_update();
}