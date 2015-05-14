#ifndef CountingLightDriver_H_
#define CountingLightDriver_H_

#include "LightDriver.h"

LightDriver CountingLightDriver_Create(int id);

//Functions only needed by tests
int CountingLightDriver_GetCallCount(LightDriver);

#endif
