/* A discrete scene playback library */

#ifndef _SCENE_H
#define _SCENE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

struct scene {
    const void *arg;
    void (*on_entrance)(const void *arg);
    void (*on_stage)(const void *arg, uint8_t stage);  // Can be NULL if num_stages == 0
    void (*on_exit)(void);
    const uint8_t num_stages;
};

void scene_enter(const struct scene *scene);
void scene_next_stage(void);
bool scene_is_active(void);

#endif // _SCENE_H