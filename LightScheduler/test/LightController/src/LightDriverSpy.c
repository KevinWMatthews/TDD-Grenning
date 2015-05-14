#include "LightDriverSpy.h"
#include "LightController.h"
#include "DataTypes.h"
#include <stdlib.h>

//Data types
typedef struct LightDriverSpyStruct
{
  LightDriverStruct base;
} LightDriverSpyStruct;

//Local function prototypes
static void turnOn(LightDriver instance);
static void turnOff(LightDriver instance);
static void destroy(LightDriver instance);

//File-scope varibles
static int states[MAX_LIGHTS];
static int lastId;
static int lastState;

static LightDriverInterfaceStruct interface =
{
  .TurnOn = turnOn,
  .TurnOff = turnOff,
  .Destroy = destroy
};

//Public functions
LightDriver LightDriverSpy_Create(int id)
{
  LightDriverSpy self = (LightDriverSpy)calloc(1, sizeof(LightDriverSpyStruct));
  self->base.vtable = &interface;
  self->base.type = "Spy";
  self->base.id = id;
  return (LightDriver)self;
}

void LightDriverSpy_InstallInterface(void)
{
  LightDriver_SetInterface(&interface);
}

void LightDriverSpy_Reset(void)
{
  int i;
  for (i = 0; i < MAX_LIGHTS; i++)
  {
    states[i] = LIGHT_STATE_UNKNOWN;
  }
  lastId = LIGHT_ID_UNKNOWN;
  lastState = LIGHT_STATE_UNKNOWN;
}

void LightDriverSpy_AddSpiesToController(void)
{
  int i;
  for (i = 0; i < MAX_LIGHTS; i++)
  {
    LightDriver spy = (LightDriver)LightDriverSpy_Create(i);
    LightController_Add(i, spy);
  }
}

int LightDriverSpy_GetState(int id)
{
  return states[id];
}

int LightDriverSpy_GetLastId(void)
{
  return lastId;
}

int LightDriverSpy_GetLastState(void)
{
  return lastState;
}

//Private functions
static void save(int id, int state)
{
  states[id] = state;
  lastId = id;
  lastState = state;
}

static void turnOn(LightDriver instance)
{
  LightDriverSpy self = (LightDriverSpy)instance;
  save(self->base.id, LIGHT_ON);
}

static void turnOff(LightDriver instance)
{
  LightDriverSpy self = (LightDriverSpy)instance;
  save(self->base.id, LIGHT_OFF);
}

static void destroy(LightDriver instance)
{
  LightDriverSpy self = (LightDriverSpy)instance;
  states[self->base.id] = LIGHT_STATE_UNKNOWN;
  free(self);
}
