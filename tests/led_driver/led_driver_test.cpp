#include "CppUTest/TestHarness.h"

extern "C" {
#include "led_driver/led_driver.h"
}

TEST_GROUP(led_driver)
{
};

/**
 * The driver is responsible for resetting every led
 * after the initialization
 */
TEST(led_driver, LedsOffAfterCreate)
{
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds);
	LONGS_EQUAL(0, virtualLeds);
}

TEST(led_driver, TurnOnLedOne)
{
	uint16_t virtualLeds;
	LedDriver_Create(&virtualLeds);
	LedDriver_TurnOn(1);
	LONGS_EQUAL(1, virtualLeds);
}
