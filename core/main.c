#include <init.h>
#include <menus.h>
#include <game.h>
#include <iev.h>
#include <music.h>
#include <tracks.h>
#include <hal/timers.h>

static struct {
    enum __attribute__((packed)) {
        GIO_INPUT,
        GIO_OUTPUT
    } type;
    union {
        struct game_input input;
        struct game_output output;
    };
} game_io;

void loop_menu(void);
void loop_game(void);
void loop_scene(void);

int main(void)
{
    init_hal();
    init_drivers();

    night_menu.io = &game_io.input;
    pause_menu.io = &game_io.input;

    menu_enter(&main_menu);
    music_start(&track_intro);

    for (;;) {
        loop_menu();
        loop_game();
        if (game_io.type == GIO_INPUT) {
            game_enter(&game_io.input);
        } else {
            game_get_results(&game_io.output);
            switch (game_io.output.status) 
            {
            case GS_PAUSE: 
                menu_enter(&pause_menu); 
                break;
            case GS_GAME_OVER:
                // TODO: show GameOver scene
                menu_enter(&main_menu);
                break;
            case GS_NIGHT_COMPLETED:
                // TODO: show Victory scene
                menu_enter(&main_menu);
                break;
            }
        }
        
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
    game_io.type = GIO_INPUT;
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
    game_io.type = GIO_OUTPUT;
}