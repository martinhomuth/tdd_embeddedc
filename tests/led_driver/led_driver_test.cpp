#include "CppUTest/TestHarness.h"

extern "C" {
#include "led_driver/led_driver.h"
#include "RuntimeErrorStub.h"
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

TEST(led_driver, OutOfBoundsTurnOnDoesNoHarm)
{
	LedDriver_TurnOn(-1);
	LedDriver_TurnOn(0);
	LedDriver_TurnOn(17);
	LedDriver_TurnOn(3141);
	LONGS_EQUAL(0, virtualLeds);
}

TEST(led_driver, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_TurnAllOn();

	LedDriver_TurnOff(-1);
	LedDriver_TurnOff(0);
	LedDriver_TurnOff(17);
	LedDriver_TurnOff(3141);
	LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(led_driver, OutOfBoundsProducesRuntimeError)
{
	LedDriver_TurnOn(-1);
	STRCMP_EQUAL("LED Driver: out-of-bounds LED",
		     RuntimeErrorStub_GetLastError());
	CHECK_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

TEST(led_driver, IsOn)
{
	CHECK_FALSE(LedDriver_IsOn(11));
	LedDriver_TurnOn(11);
	CHECK_TRUE(LedDriver_IsOn(11));
}

TEST(led_driver, OutOfBoundsLedsAreAlwaysOff)
{
	CHECK_FALSE(LedDriver_IsOn(0));
	CHECK_FALSE(LedDriver_IsOn(17));
	CHECK_TRUE(LedDriver_IsOff(0));
	CHECK_TRUE(LedDriver_IsOff(17));
}

TEST(led_driver, IsOff)
{
	CHECK_TRUE(LedDriver_IsOff(12));
	LedDriver_TurnOn(12);
	CHECK_FALSE(LedDriver_IsOff(12));
}
