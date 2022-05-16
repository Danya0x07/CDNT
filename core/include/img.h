#ifndef _CORE_IMG_H
#define _CORE_IMG_H

#include <graphics.h>

#define DECLARE_IMG(name)   extern const struct gfx_image img_##name

DECLARE_IMG(copyright);

#endif // _CORE_IMG_H