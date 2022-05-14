/* Common menu callbacks */

#ifndef _CORE_MENU_COMMON_H
#define _CORE_MENU_COMMON_H

#include <menu.h>

void common_entrance_cb(struct menu *);
void common_value_change_cb(struct menu *);
void common_view_deinit_cb(struct menu *);

#endif // _CORE_MENU_COMMON_H