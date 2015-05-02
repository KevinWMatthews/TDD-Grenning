#include "Flash.h"
#include "m28w160ect.h"

int Flash_Write(ioAddress address, ioData data)
{
  IO_Write(CommandRegister, ProgramCommand);
  IO_Write(address, data);
  while (IO_Read(StatusRegister) == 0)
  {
    ;   // Loop until ready; not dangerous at all ;)
  }
  IO_Read(address);
  return FLASH_SUCCESS;
}
