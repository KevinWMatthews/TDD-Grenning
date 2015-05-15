extern "C"
{
  #include "LedDriver_MemoryMapped.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LedDriver_MemoryMapped.h"

static uint16_t virtualLeds;

TEST_GROUP(LedDriver_MemoryMapped)
{
  LedDriver ledDriver;

  void setup()
  {
    ledDriver = LedDriver_Create(&virtualLeds);
  }

  void teardown()
  {
    LedDriver_Destroy(&ledDriver);
  }
};

//*** The Tests! ***//
TEST(LedDriver_MemoryMapped, AllFunctionsCanHandleNullPointer)
{
  CHECK_FALSE(LedDriver_IsOn(NULL, 1));
  CHECK_TRUE(LedDriver_IsOff(NULL, 1));
  LedDriver_TurnOn(NULL, 1);
  LedDriver_TurnOff(NULL, 1);
  LedDriver_TurnAllOn(NULL);
  LedDriver_TurnAllOff(NULL);
}

TEST(LedDriver_MemoryMapped, Create)
{

}

TEST(LedDriver_MemoryMapped, DestroyCanHandleNullPointer)
{
  LedDriver_Destroy(NULL);
}

TEST(LedDriver_MemoryMapped, DestroyClearsPointer)
{
  LedDriver_Destroy(&ledDriver);
  POINTERS_EQUAL(NULL, ledDriver);
}

TEST(LedDriver_MemoryMapped, CanDestroySameBufferTwice)
{
  LedDriver_Destroy(&ledDriver);
  LedDriver_Destroy(&ledDriver);
}

TEST(LedDriver_MemoryMapped, LedsOffAfterCreate)
{
  virtualLeds = 0xffff;
  LedDriver_Create(&virtualLeds);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver_MemoryMapped, TurnOnLedOne)
{
  LedDriver_TurnOn(ledDriver, 1);
  LONGS_EQUAL(1, virtualLeds);
}

TEST(LedDriver_MemoryMapped, TurnOffLedOne)
{
  LedDriver_TurnOn(ledDriver, 1);
  LedDriver_TurnOff(ledDriver, 1);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver_MemoryMapped, TurnOnMultipleLeds)
{
  LedDriver_TurnOn(ledDriver, 9);
  LedDriver_TurnOn(ledDriver, 8);
  LONGS_EQUAL(0x0180, virtualLeds);
}

TEST(LedDriver_MemoryMapped, TurnOnAllLeds)
{
  LedDriver_TurnAllOn(ledDriver);
  LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver_MemoryMapped, TurnOffAllLeds)
{
  LedDriver_TurnAllOn(ledDriver);
  LedDriver_TurnAllOff(ledDriver);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver_MemoryMapped, TurnOffAnyLed)
{
  LedDriver_TurnAllOn(ledDriver);
  LedDriver_TurnOff(ledDriver, 8);
  LONGS_EQUAL(0xff7f, virtualLeds);
}

TEST(LedDriver_MemoryMapped, LedMemoryIsNotReadable)
{
  virtualLeds = 0xffff;
  LedDriver_TurnOn(ledDriver, 8);
  LONGS_EQUAL(0x80, virtualLeds);
}

TEST(LedDriver_MemoryMapped, UpperAndLowerBounds)
{
  LedDriver_TurnOn(ledDriver, 1);
  LedDriver_TurnOn(ledDriver, 16);
  LONGS_EQUAL(0x8001, virtualLeds);
}

TEST(LedDriver_MemoryMapped, OutOfBoundsTurnOnDoesNoHarm)
{
  LedDriver_TurnOn(ledDriver, -1); //Why isn't this a compiler error?
  LedDriver_TurnOn(ledDriver, 0);
  LedDriver_TurnOn(ledDriver, 17);
  LedDriver_TurnOn(ledDriver, 33);
  LedDriver_TurnOn(ledDriver, 255);

  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver_MemoryMapped, OutOfBoundsTurnOffDoesNoHarm)
{
  LedDriver_TurnAllOn(ledDriver);

  LedDriver_TurnOff(ledDriver, -1); //Why isn't this a compiler error?
  LedDriver_TurnOff(ledDriver, 0);
  LedDriver_TurnOff(ledDriver, 17);
  LedDriver_TurnOff(ledDriver, 33);
  LedDriver_TurnOff(ledDriver, 255);

  LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver_MemoryMapped, IsOn)
{
  CHECK_FALSE(LedDriver_IsOn(ledDriver, 11));
  LedDriver_TurnOn(ledDriver, 11);
  CHECK_TRUE(LedDriver_IsOn(ledDriver, 11));
}

TEST(LedDriver_MemoryMapped, IsOff)
{
  CHECK_TRUE(LedDriver_IsOff(ledDriver, 11));
  LedDriver_TurnOn(ledDriver, 11);
  CHECK_FALSE(LedDriver_IsOff(ledDriver, 11));
}

TEST(LedDriver_MemoryMapped, OutOfBoundsLedsAreAlwaysOff)
{
  CHECK_FALSE(LedDriver_IsOn(ledDriver, 0));
  CHECK_TRUE(LedDriver_IsOff(ledDriver, 0));
  CHECK_FALSE(LedDriver_IsOn(ledDriver, 17));
  CHECK_TRUE(LedDriver_IsOff(ledDriver, 17));
}
