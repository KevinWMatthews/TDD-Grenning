#ifndef LedDriverPrivate_H_
#define LedDriverPrivate_H_

typedef struct LedDriverStruct
{
  const char * type;
} LedDriverStruct;

typedef struct LedDriverInterfaceStruct
{
  void (*TurnOn)(LedDriver self, uint8_t ledNumber);
  void (*TurnOff)(LedDriver self, uint8_t ledNumber);
  void (*TurnAllOn)(LedDriver self);
  void (*TurnAllOff)(LedDriver self);
  BOOL (*IsOn)(LedDriver self, uint8_t ledNumber);
  BOOL (*IsOff)(LedDriver self, uint8_t ledNumber);
} LedDriverInterfaceStruct;

void LedDriver_SetInterface(LedDriverInterface);

#endif
