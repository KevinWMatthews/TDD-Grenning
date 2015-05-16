#include "LedDriver.h"

static LedDriverInterface interface = NULL;

void LedDriver_SetInterface(LedDriverInterface i)
{
  interface = i;
}

const char * LedDriver_GetDriverType(LedDriver self)
{
  return self->driverType;
}

BOOL isValid(LedDriver self)
{
  return (interface && self);
}

void LedDriver_Destroy(LedDriver * self)
{
  CHECK_NULL(self);
  if (isValid(*self) && interface->Destroy)
    interface->Destroy(self);
}

void LedDriver_TurnOn(LedDriver self, uint8_t ledNumber)
{
  if (isValid(self) && interface->TurnOn)
    interface->TurnOn(self, ledNumber);
}

void LedDriver_TurnOff(LedDriver self, uint8_t ledNumber)
{
  if (isValid(self) && interface->TurnOff)
    interface->TurnOff(self, ledNumber);
}

void LedDriver_TurnAllOn(LedDriver self)
{
  if (isValid(self) && interface->TurnAllOn)
    interface->TurnAllOn(self);
}

void LedDriver_TurnAllOff(LedDriver self)
{
  if (isValid(self) && interface->TurnAllOff)
    interface->TurnAllOff(self);
}

BOOL LedDriver_IsOn(LedDriver self, uint8_t ledNumber)
{
  if (isValid(self) && interface->IsOn)
  {
    return interface->IsOn(self, ledNumber);
  }
  return FALSE;
}

BOOL LedDriver_IsOff(LedDriver self, uint8_t ledNumber)
{
  if (isValid(self) && interface->IsOn)
  {
    return interface->IsOff(self, ledNumber);
  }
  return TRUE;
}
