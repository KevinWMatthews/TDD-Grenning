#ifndef D_FLASH_H_
#define D_FLASH_H_

#include "IO.h"

int Flash_Write(ioAddress address, ioData data);

typedef enum
{
  FLASH_SUCCESS = 0,
  FLASH_VPP_ERROR
} FlashStatus;

#endif
