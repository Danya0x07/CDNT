#ifndef _CORE_GAME_CAMERA_H
#define _CORE_GAME_CAMERA_H

#include <house.h>

void camera_select(enum camera no);
void camera_enable_uv(void);
void camera_disable_uv(void);
bool camera_is_working(void);
enum camera camera_get_no(void);
enum camera_mode camera_get_mode(void);

#endif // _CORE_GAME_CAMERA_H