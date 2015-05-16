#ifndef LedDriver_MemoryMapped_H_
#define LedDriver_MemoryMapped_H_

#include "LedDriver.h"
#include <stdint.h>
#include "DataTypes.h"

typedef struct LedDriver_MemoryMappedStruct * LedDriver_MemoryMapped;

LedDriver LedDriver_MemoryMapped_Create(uint16_t * address);

#endif
