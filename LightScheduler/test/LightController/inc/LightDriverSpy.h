#ifndef LightDriverSpy_H_
#define LightDriverSpy_H_

#include "LightDriver.h"

typedef struct LightDriverSpyStruct * LightDriverSpy;

LightDriver LightDriverSpy_Create(int id);
void LightDriverSpy_InstallInterface(void);
void LightDriverSpy_Reset(void);
void LightDriverSpy_AddSpiesToController(void);

int LightDriverSpy_GetState(int id);
int LightDriverSpy_GetLastId(void);
int LightDriverSpy_GetLastState(void);

enum
{
  LIGHT_ID_UNKNOWN = -1,
  LIGHT_STATE_UNKNOWN = -1,
  LIGHT_OFF = 0,
  LIGHT_ON = 1
};

#endif  // D_LightDriverSpy_H
