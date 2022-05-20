#include <tracks.h>
#include <avr/pgmspace.h>

#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960

#define DEFINE_TRACK(name, ...) \
static const PROGMEM uint16_t notes_##name[][2] = { \
    __VA_ARGS__ \
}; \
struct music_track track_##name = { \
    &notes_##name[0], \
    sizeof(notes_##name) / sizeof(notes_##name[0]), \
    true \
}

DEFINE_TRACK(value_change, {330, 50});
DEFINE_TRACK(cursor_move, {440, 50});
DEFINE_TRACK(screen_transit, {660, 50});
DEFINE_TRACK(intro, {800, 300}, {1000, 150}, {1200, 300}, {1000, 150}, {800, 300});
DEFINE_TRACK(night_begins, {NOTE_F4, 800}, {NOTE_G4, 400}, {NOTE_GS4, 400}, {NOTE_CS5, 800}, {NOTE_C5, 800});
DEFINE_TRACK(night_completed, 
    {NOTE_D4, 200}, {NOTE_G4, 800}, 
    {NOTE_D4, 200}, {NOTE_A4, 800}, 
    {NOTE_D4, 200}, {NOTE_A4, 400},
    {NOTE_C5, 200}, {NOTE_B4, 800});
DEFINE_TRACK(night_failed,
    {NOTE_GS4, 400}, {NOTE_G4, 400}, {NOTE_FS4, 800});
DEFINE_TRACK(cam_switch, {200, 100});
DEFINE_TRACK(cam_uv_switch, {1400, 100});
DEFINE_TRACK(flash, {2000, 100}, {2000, 100}, {2000, 200});
DEFINE_TRACK(power_off, {NOTE_GS5, 200}, {NOTE_DS5, 200}, {NOTE_GS4, 200}, {NOTE_AS4, 300});
DEFINE_TRACK(lamps_on, {NOTE_A4, 100}, {NOTE_E5, 100});
DEFINE_TRACK(lamps_off, {NOTE_E5, 100}, {NOTE_A4, 100});
DEFINE_TRACK(irc_typing, 
    {400, 150}, {0, 50}, 
    {400, 70}, {0, 50},
    {400, 70}, {0, 50},
    {400, 150}, {0, 50},
    {400, 70});
DEFINE_TRACK(cam_nosignal, {100, 700});
DEFINE_TRACK(screamer1, {1000, 200}, {950, 200}, {1000, 200}, {950, 200}, {1000, 200}, {950, 200});
DEFINE_TRACK(screamer2, {1600, 200}, {1550, 200}, {1600, 200}, {1550, 200}, {1600, 200}, {1500, 200});
DEFINE_TRACK(screamer3, {400, 200}, {380, 200}, {400, 200}, {380, 200}, {400, 200}, {380, 200});
DEFINE_TRACK(_melody, 
    {NOTE_C6, 200}, {NOTE_C6, 200},
    {NOTE_G5, 200}, {NOTE_C6, 200}, {NOTE_E6, 400},
    {NOTE_D6, 200}, {NOTE_D6, 200},
    {NOTE_G5, 200}, {NOTE_D6, 200}, {NOTE_C6, 400});
