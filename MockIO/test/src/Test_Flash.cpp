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
  void setup()
  {
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
  ioAddress address = 0x1000;
  ioData data = 0xBEEF;
  int result = -1;

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
