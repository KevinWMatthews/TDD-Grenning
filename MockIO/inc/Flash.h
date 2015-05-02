#ifndef D_FLASH_H_
#define D_FLASH_H_

#include "IO.h"

int Flash_Write(ioAddress address, ioData data);

typedef enum
{
  FLASH_SUCCESS = 0,
  FLASH_VPP_ERROR,
  FLASH_PROGRAM_ERROR,
  FLASH_PROTECTED_BLOCK_ERROR,
  FLASH_UNKNOWN_PROGRAM_ERROR,
  FLASH_READ_BACK_ERROR
} FlashStatus;

#endif
