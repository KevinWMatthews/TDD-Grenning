extern "C"
{
  #include "Flash.h"  // Code under test
  #include "IO.h"     // Communicate with hardware
  #include "m28w160ect.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_Flash.h"

TEST_GROUP(Flash)
{
  ioAddress address;
  ioData data;
  int result;

  void setup()
  {
    address = 0x1000;
    data = 0xBEEF;
    result = -1;
  }
  void teardown()
  {
    mock().clear();
  }
};


// Writing out Mock functions here, though I'll probably move this to a MockIO file later
void IO_Write(ioAddress addr, ioData data)
{
  mock().actualCall("IO_Write")
        .withParameter("addr", (int)addr)   // for some reason uint32_t won't be converted to int properly on Linux
        .withParameter("data", data);
}

ioData IO_Read(ioAddress addr)
{
  mock().actualCall("IO_Read")
        .withParameter("addr", (int)addr);
  return mock().intReturnValue();
}

TEST(Flash, WriteSucceeds_ReadyImmediately)
{
  // MockIO_Expect_Write(CommandRegister, ProgramCommand);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", ProgramCommand);
  // MockIO_Expect_Write(address, data);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", (int)address)
        .withParameter("data", data);
  // MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)StatusRegister)
        .andReturnValue(ReadyBit);
  // MockIO_Expect_ReadThenReturn(address, data);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)address)
        .andReturnValue(data);
  result = Flash_Write(address, data);
  LONGS_EQUAL(FLASH_SUCCESS, result);
  mock().checkExpectations();
}

TEST(Flash, SucceedsNotImmediatelyReady)
{
  // MockIO_Expect_Write(CommandRegister, ProgramCommand);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", ProgramCommand);
  // MockIO_Expect_Write(address, data);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", (int)address)
        .withParameter("data", data);
  // MockIO_Expect_ReadThenReturn(StatusRegister, 0);
  // MockIO_Expect_ReadThenReturn(StatusRegister, 0);
  // MockIO_Expect_ReadThenReturn(StatusRegister, 0);
  mock().expectNCalls(3, "IO_Read")
        .withParameter("addr", (int)StatusRegister)
        .andReturnValue(0);
  // MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)StatusRegister)
        .andReturnValue(ReadyBit);
  // MockIO_Expect_ReadThenReturn(address, data);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)address)
        .andReturnValue(data);

  result = Flash_Write(address, data);
  LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_VppError)
{
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", ProgramCommand);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", (int)address)
        .withParameter("data", data);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)StatusRegister)
        .andReturnValue(ReadyBit | VppErrorBit);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", Reset);

  result = Flash_Write(address, data);
  LONGS_EQUAL(FLASH_VPP_ERROR, result);
}

TEST(Flash, WriteFails_ProgramError)
{
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", ProgramCommand);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", (int)address)
        .withParameter("data", data);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)StatusRegister)
        .andReturnValue(ReadyBit | ProgramErrorBit);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", Reset);

  result = Flash_Write(address, data);
  LONGS_EQUAL(FLASH_PROGRAM_ERROR, result);
}

TEST(Flash, WriteFails_ProtectedBlockError)
{
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", ProgramCommand);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", (int)address)
        .withParameter("data", data);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)StatusRegister)
        .andReturnValue(ReadyBit | BlockProtectionErrorBit);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", Reset);

    result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_PROTECTED_BLOCK_ERROR, result);
}

TEST(Flash, WriteFails_FlashUnknownProgramError)
{
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", ProgramCommand);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", (int)address)
        .withParameter("data", data);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)StatusRegister)
        .andReturnValue(ReadyBit |  EraseSuspendBit | EraseErrorBit | ProgramSuspendBit | ReservedBit);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", Reset);

  result = Flash_Write(address, data);

  LONGS_EQUAL(FLASH_UNKNOWN_PROGRAM_ERROR, result);
}

TEST(Flash, WriteFails_FlashReadBackError)
{
  mock().expectOneCall("IO_Write")
        .withParameter("addr", CommandRegister)
        .withParameter("data", ProgramCommand);
  mock().expectOneCall("IO_Write")
        .withParameter("addr", (int)address)
        .withParameter("data", data);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)StatusRegister)
        .andReturnValue(ReadyBit);
  mock().expectOneCall("IO_Read")
        .withParameter("addr", (int)address)
        .andReturnValue(data-1);    // bad data

  result = Flash_Write(address, data);

    LONGS_EQUAL(FLASH_READ_BACK_ERROR, result);
}
