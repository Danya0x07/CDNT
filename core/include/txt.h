#ifndef _CORE_TXT_H
#define _CORE_TXT_H

#include <config.h>

// Language-independent text labels.
extern const char txt_title[];
extern const char txt_subtitle[];
extern const char txt_developer[];
extern const char txt_version[];
extern const char txt_gameover_cmt[];
extern const char txt_victory_cmt[];
extern const char txt_custom_night[];
extern const char txt_setup[];
extern const char txt_cam[];

// Language-dependent text labels.
extern const char txt_play[];
extern const char txt_instructions[];
extern const char txt_continue[];
extern const char txt_exit[];
extern const char txt_night[];
extern const char txt_pause[];
extern const char txt_hours[];
extern const char txt_attacks[];
extern const char txt_night_failed[];
extern const char txt_night_completed[];
extern const char txt_nopower[];

// Text labels groups.
extern const char *const txts_instructions[];
extern const char *const txts_dialogs[NIGHTS_MAX][2];

#endif // _CORE_TXT_H