#include "led_driver/led_driver.h"

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

void LedDriver_Create(uint16_t *address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

void LedDriver_TurnOn(int led_number)
{
	if (led_number <= 0 || led_number > 16)
		return;

	ledsImage |= convertLedNumberToBit(led_number);
	updateHardware();
}

void LedDriver_TurnOff(int led_number)
{
	if (led_number <= 0 || led_number > 16)
		return;

	ledsImage &= ~convertLedNumberToBit(led_number);
	updateHardware();
}

void LedDriver_TurnAllOn()
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

