#ifndef D_LightController_H_
#define D_LightController_H_

#include "LightDriver.h"
#include "DataTypes.h"

#define MAX_LIGHTS 32

void LightController_Create(void);
void LightController_Destroy(void);
BOOL LightController_Add(int id, LightDriver);
BOOL LightController_Remove(int id);
void LightController_On(int id);
void LightController_Off(int id);

#endif
