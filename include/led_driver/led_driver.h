#ifndef __LED_DRIVER_H
#define __LED_DRIVER_H

#include <stdint.h>

void LedDriver_Create(uint16_t *);
void LedDriver_TurnOn(uint8_t);
void LedDriver_TurnOff(uint8_t);

#endif
