#ifndef D_LightDriver_H_
#define D_LightDriver_H_

typedef struct LightDriverStruct* LightDriver;

typedef enum LightDriverType
{
  TestLightDriver,    // Wait, this is test code!
  X10,
  AcmeWireless,
  MemoryMapped
} LightDriverType;

typedef struct LightDriverStruct
{
  LightDriverType type;
  int id;
} LightDriverStruct;

#endif
