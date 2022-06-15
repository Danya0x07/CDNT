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
const PROGMEM char txt_cam[] = "CAM";

#if LANGUAGE == LANG_RU

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
const PROGMEM char txt_nopower[] = "Нет\nэнергии";

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

const PROGMEM char _dialog_ans1[] = 
//  |                          |
    "\tСмотри, придёт Жёлтый - "
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
    "него работает обычная\n"
    "вспышка. Удачи!"
    ;

const PROGMEM char _dialog_ans3[] = 
//  |                          |
    "\tИногда они вселяются в\n"
    "бытовые приборы, особенно "
    "лампы. Чтобы изгнать, нуж\n"
    "но удалённо выключить\n"
    "оккупированный прибор.\n"
    "Если сигнал с камеры про\n"
    "падёт, включи верхний свет"
    "в соответствующей комнате."
    "И не забывай про ограниче\n"
    "ние ночного тарифа!"
    ;

const PROGMEM char _dialog_ans4[] = "\tНичего нового.";
//                                  |                          |
const PROGMEM char _dialog_ans5[] = "\t..Не теряй бдительность!";

#elif LANGUAGE == LANG_EN

const PROGMEM char txt_play[] = "Play";
const PROGMEM char txt_instructions[] = "Help";
const PROGMEM char txt_continue[] = "Continue";
const PROGMEM char txt_exit[] = "Exit";
const PROGMEM char txt_night[] = "Night";
const PROGMEM char txt_pause[] = "Pause";
const PROGMEM char txt_hours[] = "Hour:";
const PROGMEM char txt_attacks[] = "Score:";
const PROGMEM char txt_night_failed[] = "Night\nfailed!";
const PROGMEM char txt_night_completed[] = "Night\ncompleted!";
const PROGMEM char txt_nopower[] = "No\npower";

static const PROGMEM char _instructions_p1[] = 
//  |                          |    26 characters of size 1 per display line
    "\tUse surveillance cameras"
    "to track paranormal\n"
    "entities.\n"
    "Switch cameras using the\n"
    "touch panel.\n"
    "\tSome things are only vi\n"
    "sible in camera's UV mode."
    "To turn it on/off, touch\n"
    "the corresponding panel zo"
    "ne again. Not all cameras\n"
    "have UV mode."
    ;

static const PROGMEM char _instructions_p2[] = 
//  |                          |
    "\tIn the chosen room you\n"
    "can turn off appliances,\n"
    "turn on/off the ceiling\n"
    "lighting. In the attic you"
    "can control flashings. For"
    "the above manipulations\n"
    "use the joystick."
    ;

static const PROGMEM char _instructions_p3[] = 
//  |                          |
    "\tTurned on household\n"
    "appliances consume energy."
    "Night tariff is limited."
    "Watch your power consump\n"
    "tion.\n"
    "Don't let paranormal stuff"
    "reach you."
    ;

// Game text dialog messages
//                                       |                          |
static const PROGMEM char _dialog_q1[] = "\tWell, I'm ready.\nWhat should I expect?";
static const PROGMEM char _dialog_q2[] = "\tSo, what to expect on\nthis night?";
static const PROGMEM char _dialog_q3[] = "\tWhat to expect this\ntime?";

const PROGMEM char _dialog_ans1[] = 
//  |                          |
    "\tWell, if Yellow comes,\n"
    "kick him away with white\n"
    "flash. Against Blue use\n"
    "the UV flash. It automati\n"
    "cally chooses the side.\n"
    "Moreover, Blue is visible"
    "only in UV camera mode.\n"
    "The attic doesn't have UV\n"
    "mode, so check in advance\n"
    "if he is nearby."
    ;

const PROGMEM char _dialog_ans2[] = 
//  |                          |
    "\tIf you spot Red, don't\n"
    "leave him unattended. When"
    "he begins moving, he does\n"
    "it very quickly. Use white"
    "flash against him.\n"
    "Good luck!"
    ;

const PROGMEM char _dialog_ans3[] = 
//  |                          |
    "\tSometimes they possess\n"
    "household appliances, espe"
    "cially lamps. To exorcise\n"
    "them, turn off the occupi\n"
    "ed appliance. If the sig\n"
    "nal from the camera is lo\n"
    "st, turn on ceiling light\n"
    "ing in the corresponding\n"
    "room. And don't forget\n"
    "about night tariff\n"
    "limitations!"
    ;

const PROGMEM char _dialog_ans4[] = "\tNothing special.";
//                                  |                          |
const PROGMEM char _dialog_ans5[] = "\t..Watch out!";

#endif // LANGUAGE

#define _dialog_q4  _dialog_q3
#define _dialog_q5  _dialog_q3

const PROGMEM char *const txts_instructions[] = {_instructions_p1, _instructions_p2, _instructions_p3};
const PROGMEM char *const txts_dialogs[NIGHTS_MAX][2] = {
    {_dialog_q1, _dialog_ans1},
    {_dialog_q2, _dialog_ans2},
    {_dialog_q3, _dialog_ans3},
    {_dialog_q4, _dialog_ans4},
    {_dialog_q5, _dialog_ans5}
};