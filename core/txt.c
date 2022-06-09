#include <config.h>
#include <avr/pgmspace.h>

const PROGMEM char txt_title[] = "Creepy Drawings";
const PROGMEM char txt_subtitle[] = "Night tariff";
const PROGMEM char txt_developer[] = "Danya0x07";
const PROGMEM char txt_version[] = "v" VERSION;

const PROGMEM char txt_gameover_cmt[] = "x_x";
const PROGMEM char txt_victory_cmt[] = "^_^";
const PROGMEM char txt_custom_night[] = "Custom night";
const PROGMEM char txt_setup[] = "setup";

const PROGMEM char txt_play[] = "Играть";
const PROGMEM char txt_instructions[] = "Инструкция";
const PROGMEM char txt_continue[] = "Продолжить";
const PROGMEM char txt_exit[] = "Выйти";
const PROGMEM char txt_night[] = "Ночь";
const PROGMEM char txt_pause[] = "Пауза";
const PROGMEM char txt_hours[] = "Час:";
const PROGMEM char txt_attacks[] = "Очки:";
const PROGMEM char txt_night_failed[] = "Ночь\nпровалена!";
const PROGMEM char txt_night_completed[] = "Ночь\nпройдена!";

static const PROGMEM char _instructions_p1[] = 
//  |                          |    26 characters of size 1 per display line
    "\tИспользуйте камеры наблю"
    "дения, чтобы следить за\n"
    "паранормальным.\n"
    "Переключайте камеры с помо"
    "щью сенсорной панели.\n"
    "\tНекоторые вещи видны\n"
    "только в УФ-режиме камеры."
    "Чтобы включить УФ-режим\n"
    "выбранной камеры, косните\n"
    "сь её зоны на панели пов\n"
    "торно. Не у всех камер\n"
    "есть УФ-режим."
    ;

static const PROGMEM char _instructions_p2[] = 
//  |                          |
    "\tВ выбранной комнате мож\n"
    "но выключать бытовые осве\n"
    "тительные приборы, вклю\n"
    "чать и выключать потолоч\n"
    "ный свет. На чердаке можно"
    "управлять вспышками. Для \n"
    "вышеперечисленных манипуля"
    "ций используйте джойстик."
    ;

static const PROGMEM char _instructions_p3[] = 
//  |                          |
    "\tВключённые приборы потре"
    "бляют электроэнергию.\n"
    "Ночной тариф ограничен.\n"
    "Следите за энергопотребле\n"
    "нием.\n"
    "Не дайте паранормальному\n"
    "добраться до вас."
    ;

// Game text dialog messages
//                                       |                          |
static const PROGMEM char _dialog_q1[] = "\tЧто ж, я готов.\nЧего мне ожидать?";
static const PROGMEM char _dialog_q2[] = "\tИтак, чего мне ожидать\nв эту ночь?";
static const PROGMEM char _dialog_q3[] = "\tЧего ожидать в этот раз?";
#define _dialog_q4  _dialog_q3
#define _dialog_q5  _dialog_q3

const PROGMEM char _dialog_ans1[] = 
//  |                          |
    "\tСмотри, явится Жёлтый - "
    "прогоняй его вспышкой.\n"
    "Синего видно только в УФ, "
    "и против него нужна\n"
    "УФ-вспышка. На чердаке нет"
    "УФ-режима у камеры, так\n"
    "что смотри заранее, нет ли"
    "Синего поблизости."
    ;

const PROGMEM char _dialog_ans2[] = 
//  |                          |
    "\tЕсли заметишь Красного, "
    "не оставляй его без присмо"
    "тра. как только он начнёт "
    "двигаться, он будет делать"
    "это очень быстро. Против\n"
    "него подойдёт обычная\n"
    "вспышка. Удачи!"
    ;

const PROGMEM char _dialog_ans3[] = 
//  |                          |
    "\tИногда они вселяются в\n"
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

const PROGMEM char _dialog_ans4[] = "\tНичего нового.";
//                                  |                          |
const PROGMEM char _dialog_ans5[] = "\t..Не теряй бдительность!";

const PROGMEM char *const txts_instructions[] = {_instructions_p1, _instructions_p2, _instructions_p3};
const PROGMEM char *const txts_dialogs[NIGHTS_MAX][2] = {
    {_dialog_q1, _dialog_ans1},
    {_dialog_q2, _dialog_ans2},
    {_dialog_q3, _dialog_ans3},
    {_dialog_q4, _dialog_ans4},
    {_dialog_q5, _dialog_ans5}
};