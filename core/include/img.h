#ifndef _CORE_IMG_H
#define _CORE_IMG_H

#include <graphics.h>

#define DECLARE_IMG(name)   extern const struct gfx_image img_##name

DECLARE_IMG(copyright);
DECLARE_IMG(arrowup);
DECLARE_IMG(arrowdown);
DECLARE_IMG(ghost);
DECLARE_IMG(lamp_poltergeist);
DECLARE_IMG(cam_poltergeist);

#endif // _CORE_IMG_H