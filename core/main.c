#include <init.h>
#include <menus.h>
#include <game.h>
#include <iev.h>
#include <music.h>
#include <tracks.h>
#include <hal/timers.h>

int main(void)
{
    struct game_input ginp;
    enum joystick_event jev;
    uint32_t now = 0;
    uint8_t btnev;

    init_hal();
    init_drivers();

    night_menu.io = &ginp;

    menu_set_current(&main_menu);
    music_start(&track_intro);

    for (;;) {
        if (menu_is_active()) {
            if (ms_passed() - now >= 50) {
                jev = iev_poll_joystick();
                switch (jev) {
                    case JEV_NOTHING:
                    default:
                        break;
                    case JEV_UP:    menu_execute(MENU_CMD_DEC);  break;
                    case JEV_DOWN:  menu_execute(MENU_CMD_INC);  break;
                    case JEV_LEFT:  menu_execute(MENU_CMD_PREV); break;
                    case JEV_RIGHT: menu_execute(MENU_CMD_NEXT); break;
                }
                now = ms_passed();
            }             
        }
        music_update();
    }
}