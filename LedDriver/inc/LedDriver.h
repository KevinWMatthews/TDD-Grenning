#ifndef LedDriver_H_
#define LedDriver_H_

#include <stdint.h>
#include "DataTypes.h"

void LedDriver_Create(uint16_t* address);
void LedDriver_TurnOn(uint8_t ledNumber);
void LedDriver_TurnOff(uint8_t ledNumber);
void LedDriver_TurnAllOn(void);
void LedDriver_TurnAllOff(void);
BOOL LedDriver_IsOn(uint8_t ledNumber);
BOOL LedDriver_IsOff(uint8_t ledNumber);

#endif
