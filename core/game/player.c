#include "player.h"

struct player_request request_get(enum joystick_event jev, uint8_t btnev, enum camera cam)
{
    static bool uv = false;
    struct player_request pr = {.type = PR_NOTHING};
    uint8_t btn_pressed = PRESSED_BUTTON(btnev);
    uint8_t btn_released = RELEASED_BUTTON(btnev);

    if (btn_pressed) {
        pr.cam = btn_pressed - 1;
        if (pr.cam == cam) {
            pr.type = PR_UV_ON;
            uv = true;
        } else {
            pr.type = PR_SELECT_CAM;
        }
    } else if (btn_released) {
        pr.cam = btn_released - 1;
        if (pr.cam == cam && uv) {
            pr.type = PR_UV_OFF;
            uv = false;
        }
    }

    switch (jev) {
        case JEV_NOTHING: break;
        case JEV_UP:
            if (cam == CAMP) {
                pr.type = PR_PAUSE;
            } else {
                pr.type = PR_SELECT_CAM;
                pr.cam = CAMP;
            }
            break;

        case JEV_DOWN:
            if (cam == CAMP) {
                pr.type = PR_UVFLASH;
            } else {
                pr.type = PR_CEILING_TG;
                pr.ceiling = (enum ceiling)cam;
            }
            break;
        
        case JEV_LEFT:
            switch (cam) {
                default:
                case CAM1:
                case CAM2:
                case CAM5:
                case CAM4:
                    break;

                case CAM3:
                    pr.type = PR_LAMP_OFF;
                    pr.lamp = RL_R3_DESK;
                    break;
                
                case CAM6:
                    pr.type = PR_LAMP_OFF;
                    pr.lamp = RL_R6_DESK;
                    break;
                
                case CAM7:
                    pr.type = PR_LAMP_OFF;
                    pr.lamp = RL_R7_DESK;
                    break;
                
                case CAMP:
                    pr.type = PR_WFLASH_L;
                    break;
            }
            break;
        
        case JEV_RIGHT:
            switch (cam) {
                default:
                case CAM1:
                case CAM2:
                case CAM5:
                    break;

                case CAM3:
                    pr.type = PR_TV_OFF;
                    break;
                
                case CAM4:
                    pr.type = PR_LAMP_OFF;
                    pr.lamp = RL_R4_FLOOR;
                    break;
                
                case CAM6:
                    pr.type = PR_LAMP_OFF;
                    pr.lamp = RL_R6_FLOOR;
                    break;
                
                case CAM7:
                    pr.type = PR_LAMP_OFF;
                    pr.lamp = RL_R7_FLOOR;
                    break;
                
                case CAMP:
                    pr.type = PR_WFLASH_R;
                    break;
            }
    }
    return pr;
}