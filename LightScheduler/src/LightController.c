#include "LightController.h"
#include <stdlib.h>
#include <memory.h>
#include "X10LightDriver.h"
// #include "LightDriverSpy.h"
// #include "AcmeWirelessLightDriver.h"
// #include "MemMappedLightDriver.h"
// #include "common.h"
#include "DataTypes.h"

int lightType = 0;

static LightDriver lightDrivers[MAX_LIGHTS] = { NULL };

void LightController_Create(void)
{
  memset(lightDrivers, 0, sizeof(lightDrivers));
}

void LightController_Destroy(void)
{
  int i;
  for (i = 0; i < MAX_LIGHTS; i++)
  {
    LightDriver driver = lightDrivers[i];
    LightDriver_Destroy(driver);
    lightDrivers[i] = NULL;
  }
}

static BOOL isIdOutOfBounds(int id)
{
  return id < 0 || id >= MAX_LIGHTS;
}


BOOL LightController_Add(int id, LightDriver lightDriver)
{
  if (isIdOutOfBounds(id))
    return FALSE;

  if (lightDriver == NULL)
    return FALSE;

  LightDriver_Destroy(lightDrivers[id]);

  lightDrivers[id] = lightDriver;
  return TRUE;
}

BOOL LightController_Remove(int id)
{
  if (isIdOutOfBounds(id))
    return FALSE;

  if (lightDrivers[id] == NULL)
    return FALSE;

  LightDriver_Destroy(lightDrivers[id]);

  lightDrivers[id] = NULL;
  return TRUE;
}

void LightController_On(int id)
{
  LightDriver_TurnOn(lightDrivers[id]);
}

void LightController_Off(int id)
{
  LightDriver_TurnOff(lightDrivers[id]);
}
