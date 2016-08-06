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

TEST(led_driver, TurnOnMultipleLeds)
{
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	LONGS_EQUAL(0x180, virtualLeds);
}

TEST(led_driver, TurnOffAnyLed)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	LONGS_EQUAL(0xff7f, virtualLeds);
}

TEST(led_driver, AllOn)
{
	LedDriver_TurnAllOn();
	LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(led_driver, LedMemoryIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_TurnOn(8);
	LONGS_EQUAL(0x80, virtualLeds);
}

TEST(led_driver, UpperAndLowerBounds)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);
	LONGS_EQUAL(0x8001, virtualLeds);
}

TEST(led_driver, OutOfBoundsChangesNothing)
{
	LedDriver_TurnOn(-1);
	LedDriver_TurnOn(0);
	LedDriver_TurnOn(17);
	LedDriver_TurnOn(3141);
	LONGS_EQUAL(0, virtualLeds);
}
