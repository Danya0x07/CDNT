#include <unity.h>

extern void test_menu(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_menu);
    return UNITY_END();
}