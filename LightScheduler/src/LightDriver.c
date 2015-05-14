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

//Consider testing for null pointers as follows:
// if (self && self->vtable && self->vtable->TurnOn)
void LightDriver_TurnOn(LightDriver self)
{
  if (isValid(self))
    self->vtable->TurnOn(self);
}

void LightDriver_TurnOff(LightDriver self)
{
  if (isValid(self))
    self->vtable->TurnOff(self);
}

void LightDriver_Destroy(LightDriver self)
{
  if (isValid(self))
    self->vtable->Destroy(self);
}

const char* LightDriver_GetType(LightDriver driver)
{
  return driver->type;
}

int LightDriver_GetId(LightDriver driver)
{
  return driver->id;
}
