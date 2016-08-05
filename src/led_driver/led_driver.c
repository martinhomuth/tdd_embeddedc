#include "led_driver/led_driver.h"

#include <stdint.h>

static uint16_t *ledsAddress;

void LedDriver_Create(uint16_t *address)
{
	ledsAddress = address;
	*ledsAddress = 0;
}

void LedDriver_TurnOn(uint8_t led_number)
{
	*ledsAddress = 1;
}

void LedDriver_TurnOff(uint8_t led_number)
{
	*ledsAddress = 0;
}


