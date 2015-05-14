#ifndef D_LightDriverPrivate_H_
#define D_LightDriverPrivate_H_

typedef struct LightDriverStruct
{
  const char* type;
  int id;
} LightDriverStruct;

typedef struct LightDriverInterfaceStruct
{
  void (*TurnOn)(LightDriver);
  void (*TurnOff)(LightDriver);
  void (*Destroy)(LightDriver);
} LightDriverInterfaceStruct;

#endif
