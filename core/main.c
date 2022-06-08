#include <init.h>
#include <menus.h>
#include <scenes.h>
#include <game.h>
#include <iev.h>
#include <music.h>
#include <hal/timers.h>

enum {
    STATE_MENU,
    STATE_DIALOG,
    STATE_PLAYING,
    STATE_VICTORY,
    STATE_GAMOVER
} state;

struct game_input gin;
struct game_output gout;

void loop_timeout_scene(uint16_t timeout);
void loop_trigger_scene(void);
void loop_menu(void);
void loop_game(void);

void (*loop)(void);
void transit(void);

void setup(void)
{
    night_menu.io = &gin;
    pause_menu.io = &gin;

    dialog_scene.arg = &gin;
    victory_scene.arg = &gout;
    gameover_scene.arg = &gout;

    loop = loop_menu;
    state = STATE_MENU;
}

int main(void)
{
    init_hal();
    init_drivers();

    setup();

    scene_enter(&intro_scene);
    //loop_timeout_scene(650);

    menu_enter(&main_menu);

    for (;;) {
        loop();
        transit();
    }
}

void loop_timeout_scene(uint16_t timeout)
{
    uint32_t now = ms_passed();

    while (scene_is_active()) {
        if (ms_passed() - now >= timeout) {
            scene_next_stage();
            now = ms_passed();
        }
        music_update();
    }
}

void loop_trigger_scene(void)
{
    enum joystick_event jev;

    while (scene_is_active()) {
        jev = iev_poll_joystick();
        if (jev == JEV_RIGHT)
            scene_next_stage();
        music_update();
    }
}

void loop_menu(void)
{
    enum joystick_event jev;
    
    while (menu_is_active()) {
        jev = iev_poll_joystick();
        switch (jev) {
            case JEV_NOTHING: break;
            case JEV_UP:    menu_execute(MENU_CMD_DEC);  break;
            case JEV_DOWN:  menu_execute(MENU_CMD_INC);  break;
            case JEV_LEFT:  menu_execute(MENU_CMD_PREV); break;
            case JEV_RIGHT: menu_execute(MENU_CMD_NEXT); break;
        }
        music_update();
    }
}

void loop_game(void)
{
    enum joystick_event jev;
    uint8_t btnev;

    while (game_is_active()) {
        jev = iev_poll_joystick();
        btnev = iev_poll_buttons();
        game_tick(jev, btnev, ms_passed());
        music_update();
    }
}

void transit(void)
{
    switch (state) {
        case STATE_MENU:
            if (gin.request == GR_NEW_GAME) {
                scene_enter(&dialog_scene);
                state = STATE_DIALOG;
            } else {
                game_enter(&gin);
                state = STATE_PLAYING;
            }
            break;
        
        case STATE_DIALOG:
            game_enter(&gin);
            state = STATE_PLAYING;
            break;

        case STATE_PLAYING:
            if (gout.status == GS_PAUSE) {
                menu_enter(&pause_menu);
                state = STATE_MENU;
            } else if (gout.status == GS_NIGHT_FAILED) {
                scene_enter(&gameover_scene);
                state = STATE_GAMOVER;
            } else {  // victory
                scene_enter(&victory_scene);
                state = STATE_VICTORY;
            }
            break;
        
        case STATE_GAMOVER:
        case STATE_VICTORY:
            menu_enter(&main_menu);
            state = STATE_MENU;
            break;
    }

    switch (state) {
        case STATE_MENU:    loop = loop_menu; break;
        case STATE_DIALOG:  loop = loop_trigger_scene; break;
        case STATE_PLAYING: loop = loop_game; break;
        case STATE_GAMOVER: loop = loop_trigger_scene; break;
        case STATE_VICTORY: loop = loop_trigger_scene; break;
    }
}