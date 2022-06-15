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
DECLARE_IMG(joystick);
DECLARE_IMG(flash);
DECLARE_IMG(autoflash);
DECLARE_IMG(noopt);
DECLARE_IMG(pause);
DECLARE_IMG(ceiling);
DECLARE_IMG(floorlamp);
DECLARE_IMG(desklamp);
DECLARE_IMG(tv);
DECLARE_IMG(closecam);


#endif // _CORE_IMG_H