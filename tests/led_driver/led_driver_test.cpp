#include "CppUTest/TestHarness.h"

extern "C" {
#include "led_driver/led_driver.h"
}

static uint16_t virtualLeds;

TEST_GROUP(led_driver)
{
	void setup() {
		LedDriver_Create(&virtualLeds);
	}

	void teardown() {

	}
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
	LedDriver_TurnOn(1);
	LONGS_EQUAL(1, virtualLeds);
}

TEST(led_driver, TurnOffLedOne)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	LONGS_EQUAL(0, virtualLeds);
}
