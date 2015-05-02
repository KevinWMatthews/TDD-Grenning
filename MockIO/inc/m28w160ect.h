#ifndef D_M28W160ECT_H_
#define D_M28W160ECT_H_

typedef enum
{
  CommandRegister = 0x0,
  StatusRegister = 0x0
} Flash_Registers;

typedef enum
{
  ProgramCommand = 0x40,
  Reset = 0xff
} Flash_Command;

typedef enum
{
  ReadyBit        = 1<<7,
  ProgramErrorBit = 1<<4,
  VppErrorBit     = 1<<3
} StatusRegisterBits;

#endif
