#include "camera.h"
#include "slots.h"

static enum camera_no cam_no = CAMP;
static enum camera_mode cam_mode = CAM_MODE_W;

void camera_select(enum camera_no no)
{
    cam_no = no;
    cam_mode = CAM_MODE_W;
}

void camera_enable_uv(void)
{
    cam_mode = CAM_MODE_UV;
}

void camera_disable_uv(void)
{
    cam_mode = CAM_MODE_W;
}

bool camera_is_working(void)
{
    return slot_is_free(SLOT_CAM, cam_no);
}

enum camera_no camera_get_no(void)
{
    return cam_no;
}

enum camera_mode camera_get_mode(void)
{
    return cam_mode;
}
