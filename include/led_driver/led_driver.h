#ifndef __LED_DRIVER_H
#define __LED_DRIVER_H

#include <stdint.h>

void LedDriver_Create(uint16_t *);
int LedDriver_IsOn(int);
int LedDriver_IsOff(int);
void LedDriver_TurnOn(int);
void LedDriver_TurnOff(int);
void LedDriver_TurnAllOn(void);

#endif
