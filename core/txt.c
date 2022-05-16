#include <avr/pgmspace.h>

// Menu items texts.
const PROGMEM char _txt_mi_play[] = "Играть";
const PROGMEM char _txt_mi_instructions[] = "Инструкция";
const PROGMEM char _txt_mi_continue[] = "Продолжить";
const PROGMEM char _txt_mi_exit[] = "Выйти";

// Menu labels texts.
const PROGMEM char txt_ml_night[] = "Ночь";
const PROGMEM char txt_ml_pause[] = "Пауза";
const PROGMEM char txt_ml_hours[] = "Час:";
const PROGMEM char txt_ml_attacks[] = "Очки:";
const PROGMEM char _txt_ml_instructions_p1[] = 
//  |                          |    26 characters of size 1 per display line
    "  Используйте камеры наблю"
    "дения, чтобы следить за\n"
    "паранормальным.\n"
    "Переключайте камеры с помо"
    "щью сенсорной панели.\n"
    "  Некоторые вещи видны\n"
    "только в УФ-режиме камеры."
    "Чтобы включить УФ-режим\n"
    "выбранной камеры, косните\n"
    "сь её зоны на панели пов\n"
    "торно. Не у всех камер\n"
    "есть УФ-режим."
    ;

const PROGMEM char _txt_ml_instructions_p2[] = 
//  |                          |
    "  В выбранной комнате мож\n"
    "но выключать бытовые осве\n"
    "тительные приборы, вклю\n"
    "чать и выключать потолоч\n"
    "ный свет. На чердаке можно"
    "управлять вспышками. Для \n"
    "вышеперечисленных манипуля"
    "ций используйте джойстик."
    ;

const PROGMEM char _txt_ml_instructions_p3[] = 
//  |                          |
    "  Включённые приборы потре"
    "бляют электроэнергию.\n"
    "Ночной тариф ограничен.\n"
    "Следите за энергопотребле\n"
    "нием.\n"
    "Не дайте паранормальному\n"
    "добраться до вас."
    ;

// Game text labels
const PROGMEM char txt_gl_title[] = "Creepy Drawings";
const PROGMEM char txt_gl_subtitle[] = "Night tariff";
const PROGMEM char txt_developer[] = "Danya0x07";
const PROGMEM char txt_gl_version[] = "v0.6";
const PROGMEM char txt_gl_gameover[] = "Вы проиграли!";
const PROGMEM char txt_gl_night_complete[] = "Ночь пройдена!";

// Game text dialog messages
//                                    |                          |
const PROGMEM char _txt_gd_req_n1[] = "  Что ж, я готов. Чего мне\nожидать?";
const PROGMEM char _txt_gd_req_n2[] = "  Итак, чего мне ожидать\nв эту ночь?";
const PROGMEM char _txt_gd_req_n3[] = "  Чего ожидать в этот раз?";
const char *const _txt_gd_req_n4 = _txt_gd_req_n3;
const char *const _txt_gd_req_n5 = _txt_gd_req_n3;

const PROGMEM char _txt_gd_resp_n1[] = 
//  |                          |
    "  Смотри, явится Жёлтый - "
    "прогоняй его вспышкой.\n"
    "Синего видно только в УФ, "
    "и против него нужна\n"
    "УФ-вспышка. На чердаке нет"
    "УФ-режима у камеры, так\n"
    "что смотри заранее, нет ли"
    "Синего поблизости."
    ;

const PROGMEM char _txt_gd_resp_n2[] = 
//  |                          |
    "  Если заметишь Красного, "
    "не оставляй его без присмо"
    "тра. как только он начнёт "
    "двигаться, он будет делать"
    "это очень быстро. Против\n"
    "него подойдёт обычная\n"
    "вспышка. Удачи!"
    ;

const PROGMEM char _txt_gd_resp_n3[] = 
//  |                          |
    "  Иногда они вселяются в\n"
    "бытовые приборы, особенно "
    "лампы. Чтобы изгнать, мож\n"
    "но удалённо выключить при\n"
    "бор или включить потолоч\n"
    "ное освещение в комнате.\n"
    "Последнее помогает ещё, ес"
    "ли сигнал с камеры пропал,"
    "это из-за энергетики проис"
    "ходит. И следи за энергопо"
    "треблением!."
    ;

const PROGMEM char _txt_gd_resp_n4[] = "  Ничего нового.";

//                                     |                          |
const PROGMEM char _txt_gd_resp_n5[] = "  ..Не теряй бдительность!";

// String arrays for menus.
const PROGMEM char *const txt_mainmenu[] = {_txt_mi_play, _txt_mi_instructions};
const PROGMEM char *const txt_instrmenu[] = {_txt_ml_instructions_p1, _txt_ml_instructions_p2, _txt_ml_instructions_p3};
const PROGMEM char *const txt_pausemenu[] = {_txt_mi_continue, _txt_mi_exit};