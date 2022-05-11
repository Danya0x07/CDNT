#include <unity.h>
#include <iproc.h>

void test_iproc_joystick(void)
{
    TEST_ASSERT_EQUAL(JEV_NOTHING, iproc_joystick(JPOS_CENTER));
    TEST_ASSERT_EQUAL(JEV_UP, iproc_joystick(JPOS_UP));
    TEST_ASSERT_EQUAL(JEV_NOTHING, iproc_joystick(JPOS_UP));

    TEST_ASSERT_EQUAL(JEV_NOTHING, iproc_joystick(JPOS_CENTER));
    TEST_ASSERT_EQUAL(JEV_DOWN, iproc_joystick(JPOS_DOWN));
    TEST_ASSERT_EQUAL(JEV_NOTHING, iproc_joystick(JPOS_DOWN));

    TEST_ASSERT_EQUAL(JEV_NOTHING, iproc_joystick(JPOS_CENTER));
    TEST_ASSERT_EQUAL(JEV_LEFT, iproc_joystick(JPOS_LEFT));
    TEST_ASSERT_EQUAL(JEV_NOTHING, iproc_joystick(JPOS_LEFT));

    TEST_ASSERT_EQUAL(JEV_NOTHING, iproc_joystick(JPOS_CENTER));
    TEST_ASSERT_EQUAL(JEV_RIGHT, iproc_joystick(JPOS_RIGHT));
    TEST_ASSERT_EQUAL(JEV_NOTHING, iproc_joystick(JPOS_RIGHT));

    TEST_ASSERT_EQUAL(JEV_UP, iproc_joystick(JPOS_UP));
    TEST_ASSERT_EQUAL(JEV_LEFT, iproc_joystick(JPOS_LEFT));
    TEST_ASSERT_EQUAL(JEV_DOWN, iproc_joystick(JPOS_DOWN));
    TEST_ASSERT_EQUAL(JEV_RIGHT, iproc_joystick(JPOS_RIGHT));
    TEST_ASSERT_EQUAL(JEV_NOTHING, iproc_joystick(JPOS_CENTER));
}

void test_iproc_buttons(void)
{
    TEST_ASSERT_EQUAL(0x00, iproc_buttons(0x00));
    TEST_ASSERT_EQUAL(0x02, iproc_buttons(0x01));
    TEST_ASSERT_EQUAL(0x00, iproc_buttons(0x01));
    TEST_ASSERT_EQUAL(0x20, iproc_buttons(0x00));
}