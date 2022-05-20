#include "scene.h"

static const struct scene *current_scene = NULL;
static uint8_t current_stage = 0;

void scene_enter(const struct scene *scene)
{
    current_scene = scene;
    current_stage = 0;
    scene->on_entrance(scene->arg);
}

void scene_next_stage(void)
{
    if (++current_stage > current_scene->num_stages) {
        current_scene->on_exit();
        current_scene = NULL;
        return;
    }

    current_scene->on_stage(current_scene->arg, current_stage);
}


bool scene_is_active(void)
{
    return current_scene != NULL;
}
