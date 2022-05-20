#include <unity.h>

extern void test_menu(void);
extern void test_iproc_joystick(void),
            test_iproc_buttons(void);
extern void test_scene(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_menu);
    RUN_TEST(test_iproc_joystick);
    RUN_TEST(test_iproc_buttons);
    RUN_TEST(test_scene);
    return UNITY_END();
}