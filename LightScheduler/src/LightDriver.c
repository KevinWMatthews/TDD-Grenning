#include "LightDriver.h"
#include "DataTypes.h"

static LightDriverInterface interface = NULL;

void LightDriver_SetInterface(LightDriverInterface i)
{
  interface = i;
}

//NULL checks are done by LightDriver interface, so
//none of the specific drivers need to do NULL checks.
static BOOL isValid(LightDriver self)
{
  return interface && self;   //Clever! Returns false if either is NULL
}

void LightDriver_TurnOn(LightDriver self)
{
  // Should we protect against a null pointer in interface here?
  if (isValid(self) && interface->TurnOn)
    interface->TurnOn(self);
}

void LightDriver_TurnOff(LightDriver self)
{
  // Should we protect against a null pointer in interface here?
  if (isValid(self) && interface->TurnOff)
    interface->TurnOff(self);
}

void LightDriver_Destroy(LightDriver self)
{
  if (isValid(self))
    interface->Destroy(self);
}

const char* LightDriver_GetType(LightDriver driver)
{
  return driver->type;
}

int LightDriver_GetId(LightDriver driver)
{
  return driver->id;
}
