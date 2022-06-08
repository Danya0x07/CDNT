#include "camera.h"
#include "slots.h"

static enum camera cam = CAMP;
static enum camera_mode mode = CAM_MODE_W;

void camera_select(enum camera no)
{
    cam = no;
    mode = CAM_MODE_W;
}

void camera_enable_uv(void)
{
    mode = CAM_MODE_UV;
}

void camera_disable_uv(void)
{
    mode = CAM_MODE_W;
}

bool camera_is_working(void)
{
    return slot_is_free(SLOT_CAM, cam);
}

enum camera camera_get_no(void)
{
    return cam;
}

enum camera_mode camera_get_mode(void)
{
    return mode;
}
