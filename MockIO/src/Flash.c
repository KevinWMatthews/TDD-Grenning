#include "Flash.h"
#include "m28w160ect.h"

int Flash_Write(ioAddress address, ioData data)
{
  ioData status = 0;

  IO_Write(CommandRegister, ProgramCommand);
  IO_Write(address, data);

  while ((status & ReadyBit) == 0)
  {
    status = IO_Read(StatusRegister);
  }
  if (status != ReadyBit)
  {
    IO_Write(CommandRegister, Reset);
    return FLASH_VPP_ERROR;
  }

  IO_Read(address);
  return FLASH_SUCCESS;
}
