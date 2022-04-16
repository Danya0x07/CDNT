#include <unity.h>

void test()
{
    TEST_ASSERT(1);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test);
    UNITY_END();

    for (;;) {}
}