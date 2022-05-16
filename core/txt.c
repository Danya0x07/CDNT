#include <config.h>
#include <avr/pgmspace.h>

const PROGMEM char txt_title[] = "Creepy Drawings";
const PROGMEM char txt_subtitle[] = "Night tariff";
const PROGMEM char txt_developer[] = "Danya0x07";
const PROGMEM char txt_version[] = "v" VERSION;

const PROGMEM char txt_play[] = "�����";
const PROGMEM char txt_instructions[] = "��������";
const PROGMEM char txt_continue[] = "�த������";
const PROGMEM char txt_exit[] = "���";
const PROGMEM char txt_night[] = "����";
const PROGMEM char txt_pause[] = "��㧠";
const PROGMEM char txt_hours[] = "���:";
const PROGMEM char txt_attacks[] = "�窨:";
const PROGMEM char txt_gameover[] = "�� �ந�ࠫ�!";
const PROGMEM char txt_night_complete[] = "���� �ன����!";

static const PROGMEM char _instructions_p1[] = 
//  |                          |    26 characters of size 1 per display line
    "  �ᯮ���� ������ �����"
    "�����, �⮡� ᫥���� ��\n"
    "��࠭�ଠ���.\n"
    "��४��砩� ������ � ����"
    "��� ᥭ�୮� ������.\n"
    "  ������� ��� �����\n"
    "⮫쪮 � ��-०��� ������."
    "�⮡� ������� ��-०��\n"
    "��࠭��� ������, ��᭨�\n"
    "�� �� ���� �� ������ ���\n"
    "�୮. �� � ��� �����\n"
    "���� ��-०��."
    ;

static const PROGMEM char _instructions_p2[] = 
//  |                          |
    "  � ��࠭��� ������ ���\n"
    "�� �몫���� ��⮢� �ᢥ\n"
    "�⥫�� �ਡ���, ����\n"
    "��� � �몫���� ��⮫��\n"
    "�� ᢥ�. �� �ठ�� �����"
    "�ࠢ���� ���誠��. ��� \n"
    "��襯���᫥���� �������"
    "権 �ᯮ���� �����⨪."
    ;

static const PROGMEM char _instructions_p3[] = 
//  |                          |
    "  ������� �ਡ��� ����"
    "����� �����ࣨ�.\n"
    "��筮� ��� ��࠭�祭.\n"
    "������ �� �࣮���ॡ��\n"
    "����.\n"
    "�� ���� ��࠭�ଠ�쭮��\n"
    "�������� �� ���."
    ;

// Game text dialog messages
//                                       |                          |
static const PROGMEM char _dialog_q1[] = "  �� �, � ��⮢. ���� ���\n�������?";
static const PROGMEM char _dialog_q2[] = "  �⠪, 祣� ��� �������\n� ��� ����?";
static const PROGMEM char _dialog_q3[] = "  ���� ������� � ��� ࠧ?";
#define _dialog_q4  _dialog_q3
#define _dialog_q5  _dialog_q3

const PROGMEM char _dialog_ans1[] = 
//  |                          |
    "  �����, ��� ���� - "
    "�ண��� ��� ���誮�.\n"
    "������ ����� ⮫쪮 � ��, "
    "� ��⨢ ���� �㦭�\n"
    "��-���誠. �� �ठ�� ���"
    "��-०��� � ������, ⠪\n"
    "�� ᬮ�� ��࠭��, ��� ��"
    "������ ���������."
    ;

const PROGMEM char _dialog_ans2[] = 
//  |                          |
    "  �᫨ ������� ��᭮��, "
    "�� ��⠢�� ��� ��� ��ᬮ"
    "��. ��� ⮫쪮 �� ����� "
    "���������, �� �㤥� ������"
    "�� �祭� �����. ��⨢\n"
    "���� �������� ���筠�\n"
    "���誠. ����!"
    ;

const PROGMEM char _dialog_ans3[] = 
//  |                          |
    "  ������ ��� �ᥫ����� �\n"
    "��⮢� �ਡ���, �ᮡ���� "
    "�����. �⮡� �������, ���\n"
    "�� 㤠�񭭮 �몫���� ��\n"
    "��� ��� ������� ��⮫��\n"
    "��� �ᢥ饭�� � ������.\n"
    "��᫥���� �������� ���, ��"
    "�� ᨣ��� � ������ �ய��,"
    "�� ��-�� �ࣥ⨪� �ந�"
    "室��. � ᫥�� �� �࣮��"
    "�ॡ������!."
    ;

const PROGMEM char _dialog_ans4[] = "  ��祣� ������.";
//                                  |                          |
const PROGMEM char _dialog_ans5[] = "  ..�� ��� ���⥫쭮���!";

const PROGMEM char *const txts_instructions[] = {_instructions_p1, _instructions_p2, _instructions_p3};
const PROGMEM char *const txt_dialogs[5][2] = {
    {_dialog_q1, _dialog_ans1},
    {_dialog_q2, _dialog_ans2},
    {_dialog_q3, _dialog_ans3},
    {_dialog_q4, _dialog_ans4},
    {_dialog_q5, _dialog_ans5}
};