#include <unity.h>
#include <scene.h>

static uint8_t current_stage = 0;

static void scene1_entrance_cb(const void *arg)
{
    TEST_MESSAGE("Entering scene");
}

static void scene1_stage_cb(const void *arg, uint8_t stage)
{
    ++current_stage;
    TEST_ASSERT_EQUAL(stage, current_stage);
}

struct scene scene1 = {
    .arg = NULL,
    .on_entrance = scene1_entrance_cb,
    .on_stage = scene1_stage_cb,
    .num_stages = 5
};

void test_scene(void)
{
    scene_enter(&scene1);
    while (scene_is_active()) {
        scene_next_stage();
    }
    TEST_ASSERT_EQUAL(4, current_stage);
}