#ifndef LedDriver_H_
#define LedDriver_H_

#include <stdint.h>
#include "DataTypes.h"

typedef struct LedDriverStruct * LedDriver;
typedef struct LedDriverInterfaceStruct * LedDriverInterface;


// This is the public interface
// The user should be able to call LedDriver_TurnOn() without worrying
// about anything that is behind the scenes.
// All he should have to do is initialize the LedDriver with the correct interface.

// const char* LedDriver_GetType(LedDriver);

// Create should probably belong in each specific driver.
// The argument list for initialization will probably vary.


LedDriver LedDriver_Create(uint16_t * address);
void LedDriver_Destroy(LedDriver * self);
void LedDriver_TurnOn(LedDriver self, uint8_t ledNumber);
void LedDriver_TurnOff(LedDriver self, uint8_t ledNumber);
void LedDriver_TurnAllOn(LedDriver self);
void LedDriver_TurnAllOff(LedDriver self);
BOOL LedDriver_IsOn(LedDriver self, uint8_t ledNumber);
BOOL LedDriver_IsOff(LedDriver self, uint8_t ledNumber);

#include "LedDriverPrivate.h"

#endif
