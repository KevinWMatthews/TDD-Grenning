#include "CountingLightDriver.h"
#include <stdlib.h>

//Data types
typedef struct CountingLightDriverStruct* CountingLightDriver;

typedef struct CountingLightDriverStruct
{
  LightDriverStruct base;
  int counter;
} CountingLightDriverStruct;


//File-scope function prototypes
static void count(LightDriver instance);
static void destroy(LightDriver instance);


//File-scope variables
static LightDriverInterfaceStruct interface =
{
  .TurnOn = count,
  .TurnOff = count,
  .Destroy = destroy
};


//Public functions
LightDriver CountingLightDriver_Create(int id)
{
  CountingLightDriver self = calloc(1, sizeof(CountingLightDriverStruct));
  self->base.vtable = &interface;
  self->base.type = "CountingLightDriver";
  self->base.id = id;
  return (LightDriver)self;
}

int CountingLightDriver_GetCallCount(LightDriver instance)
{
  CountingLightDriver self = (CountingLightDriver)instance;
  return self->counter;
}


//Private functions
static void count(LightDriver instance)
{
  CountingLightDriver self = (CountingLightDriver)instance;
  self->counter++;
}

static void destroy(LightDriver instance)
{}
