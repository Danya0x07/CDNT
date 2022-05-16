#include <avr/pgmspace.h>

// Menu items texts.
const PROGMEM char _txt_mi_play[] = "�����";
const PROGMEM char _txt_mi_instructions[] = "��������";
const PROGMEM char _txt_mi_continue[] = "�த������";
const PROGMEM char _txt_mi_exit[] = "���";

// Menu labels texts.
const PROGMEM char txt_ml_night[] = "����";
const PROGMEM char txt_ml_pause[] = "��㧠";
const PROGMEM char txt_ml_hours[] = "���:";
const PROGMEM char txt_ml_attacks[] = "�窨:";
const PROGMEM char _txt_ml_instructions_p1[] = 
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

const PROGMEM char _txt_ml_instructions_p2[] = 
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

const PROGMEM char _txt_ml_instructions_p3[] = 
//  |                          |
    "  ������� �ਡ��� ����"
    "����� �����ࣨ�.\n"
    "��筮� ��� ��࠭�祭.\n"
    "������ �� �࣮���ॡ��\n"
    "����.\n"
    "�� ���� ��࠭�ଠ�쭮��\n"
    "�������� �� ���."
    ;

// Game text labels
const PROGMEM char txt_gl_title[] = "Creepy Drawings";
const PROGMEM char txt_gl_subtitle[] = "Night tariff";
const PROGMEM char txt_developer[] = "Danya0x07";
const PROGMEM char txt_gl_version[] = "v0.6";
const PROGMEM char txt_gl_gameover[] = "�� �ந�ࠫ�!";
const PROGMEM char txt_gl_night_complete[] = "���� �ன����!";

// Game text dialog messages
//                                    |                          |
const PROGMEM char _txt_gd_req_n1[] = "  �� �, � ��⮢. ���� ���\n�������?";
const PROGMEM char _txt_gd_req_n2[] = "  �⠪, 祣� ��� �������\n� ��� ����?";
const PROGMEM char _txt_gd_req_n3[] = "  ���� ������� � ��� ࠧ?";
const char *const _txt_gd_req_n4 = _txt_gd_req_n3;
const char *const _txt_gd_req_n5 = _txt_gd_req_n3;

const PROGMEM char _txt_gd_resp_n1[] = 
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

const PROGMEM char _txt_gd_resp_n2[] = 
//  |                          |
    "  �᫨ ������� ��᭮��, "
    "�� ��⠢�� ��� ��� ��ᬮ"
    "��. ��� ⮫쪮 �� ����� "
    "���������, �� �㤥� ������"
    "�� �祭� �����. ��⨢\n"
    "���� �������� ���筠�\n"
    "���誠. ����!"
    ;

const PROGMEM char _txt_gd_resp_n3[] = 
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

const PROGMEM char _txt_gd_resp_n4[] = "  ��祣� ������.";

//                                     |                          |
const PROGMEM char _txt_gd_resp_n5[] = "  ..�� ��� ���⥫쭮���!";

// String arrays for menus.
const PROGMEM char *const txt_mainmenu[] = {_txt_mi_play, _txt_mi_instructions};
const PROGMEM char *const txt_instrmenu[] = {_txt_ml_instructions_p1, _txt_ml_instructions_p2, _txt_ml_instructions_p3};
const PROGMEM char *const txt_pausemenu[] = {_txt_mi_continue, _txt_mi_exit};