#ifndef LedDriver_MemoryMapped_H_
#define LedDriver_MemoryMapped_H_

#include <stdint.h>
#include "DataTypes.h"

typedef struct LedDriverStruct * LedDriver;

LedDriver LedDriver_Create(uint16_t * address);
void LedDriver_Destroy(LedDriver * self);
void LedDriver_TurnOn(LedDriver self, uint8_t ledNumber);
void LedDriver_TurnOff(LedDriver self, uint8_t ledNumber);
void LedDriver_TurnAllOn(LedDriver self);
void LedDriver_TurnAllOff(LedDriver self);
BOOL LedDriver_IsOn(LedDriver self, uint8_t ledNumber);
BOOL LedDriver_IsOff(LedDriver self, uint8_t ledNumber);

#endif
