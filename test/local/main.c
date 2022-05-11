#include <unity.h>

extern void test_menu(void);
extern void test_iproc_joystick(void),
            test_iproc_buttons(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_menu);
    RUN_TEST(test_iproc_joystick);
    RUN_TEST(test_iproc_buttons);
    return UNITY_END();
}