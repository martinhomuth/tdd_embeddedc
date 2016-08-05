#include "CppUTest/TestHarness.h"

extern "C" {
#include "led_driver/led_driver.h"
}

TEST_GROUP(led_driver)
{
};

TEST(led_driver, LedsOffAfterCreate)
{
	LONGS_EQUAL(0, 1);
}
