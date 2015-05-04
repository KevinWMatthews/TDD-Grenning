#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <memory.h>
#include "LightDriverSpy.h"
// #include "common.h"
#include "DataTypes.h"

typedef struct LightDriverSpyStruct * LightDriverSpy;
typedef struct LightDriverSpyStruct
{
    LightDriverStruct base;
} LightDriverSpyStruct;

static int states[MAX_LIGHTS];
static int lastId;
static int lastState;

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

LightDriver LightDriverSpy_Create(int id)
{
  LightDriverSpy self = (LightDriverSpy)calloc(1, sizeof(LightDriverSpyStruct));  // Huh, I wonder why I need typecasting
  self->base.type = TestLightDriver;
  self->base.id = id;
  return (LightDriver)self;
}

void LightDriverSpy_Destroy(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    states[self->base.id] = LIGHT_STATE_UNKNOWN;
    free(self);
}

static void save(int id, int state)
{
    states[id] = state;
    lastId = id;
    lastState = state;
}

void LightDriverSpy_TurnOn(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    save(self->base.id, LIGHT_ON);
}

void LightDriverSpy_TurnOff(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    save(self->base.id, LIGHT_OFF);
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

#ifdef __cplusplus
}
#endif
