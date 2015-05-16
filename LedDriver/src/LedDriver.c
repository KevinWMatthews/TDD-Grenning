#include "LedDriver.h"

static LedDriverInterface interface = NULL;

void LedDriver_SetInterface(LedDriverInterface i)
{
  interface = i;
}
