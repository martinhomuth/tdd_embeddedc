#include "led_driver/led_driver.h"
#include "util/RuntimeError.h"

#include <stdint.h>

enum { ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON };

static uint16_t *ledsAddress;
static uint16_t ledsImage;

static uint16_t convertLedNumberToBit(int led_number)
{
	return 1 << (led_number - 1);
}

static void updateHardware(void)
{
	*ledsAddress = ledsImage;
}

enum { FIRST_LED = 1, LAST_LED = 16 };

static int isLedOutOfBounds(int led_number)
{
	return (led_number < FIRST_LED) || (led_number > LAST_LED);
}

static void setLedImageBit(int led_number)
{
	ledsImage |= convertLedNumberToBit(led_number);
}

static void clearLedImageBit(int led_number)
{
	ledsImage &= ~convertLedNumberToBit(led_number);
}

void LedDriver_Create(uint16_t *address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

void LedDriver_TurnOn(int led_number)
{
	if (isLedOutOfBounds(led_number)) {
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
		return;
	}

	setLedImageBit(led_number);
	updateHardware();
}

void LedDriver_TurnOff(int led_number)
{
	if (isLedOutOfBounds(led_number)) {
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
		return;
	}

	clearLedImageBit(led_number);
	updateHardware();
}

void LedDriver_TurnAllOn()
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

int LedDriver_IsOn(int led_number)
{
	if (isLedOutOfBounds(led_number))
		return 0;

	return ledsImage & (convertLedNumberToBit(led_number));
}

int LedDriver_IsOff(int led_number)
{
	return !(LedDriver_IsOn(led_number));
}

