extern "C"
{
  #include <stdint.h>
  #include "LedDriver.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LedDriver.h"

static uint16_t virtualLeds;

TEST_GROUP(Test_LedDriver)
{
  void setup()
  {
    LedDriver_Create(&virtualLeds);
  }

  void teardown()
  {
  }
};

//*** The Tests! ***//
TEST(Test_LedDriver, LedsOffAfterCreate)
{
  virtualLeds = 0xffff;
  LedDriver_Create(&virtualLeds);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(Test_LedDriver, TurnOnLedOne)
{
  LedDriver_TurnOn(1);
  LONGS_EQUAL(1, virtualLeds);
}

TEST(Test_LedDriver, TurnOffLedOne)
{
  LedDriver_TurnOn(1);
  LedDriver_TurnOff(1);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(Test_LedDriver, TurnOnMultipleLeds)
{
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  LONGS_EQUAL(0x0180, virtualLeds);
}

TEST(Test_LedDriver, TurnOnAllLeds)
{
  LedDriver_TurnAllOn();
  LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(Test_LedDriver, TurnOffAllLeds)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnAllOff();
  LONGS_EQUAL(0, virtualLeds);
}

TEST(Test_LedDriver, TurnOffAnyLed)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(8);
  LONGS_EQUAL(0xff7f, virtualLeds);
}

TEST(Test_LedDriver, LedMemoryIsNotReadable)
{
  virtualLeds = 0xffff;
  LedDriver_TurnOn(8);
  LONGS_EQUAL(0x80, virtualLeds);
}

TEST(Test_LedDriver, UpperAndLowerBounds)
{
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(16);
  LONGS_EQUAL(0x8001, virtualLeds);
}

TEST(Test_LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
  LedDriver_TurnOn(-1); //Why isn't this a compiler error?
  LedDriver_TurnOn(0);
  LedDriver_TurnOn(17);
  LedDriver_TurnOn(33);
  LedDriver_TurnOn(255);

  LONGS_EQUAL(0, virtualLeds);
}

TEST(Test_LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
  LedDriver_TurnAllOn();

  LedDriver_TurnOff(-1); //Why isn't this a compiler error?
  LedDriver_TurnOff(0);
  LedDriver_TurnOff(17);
  LedDriver_TurnOff(33);
  LedDriver_TurnOff(255);

  LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(Test_LedDriver, IsOn)
{
  CHECK_FALSE(LedDriver_IsOn(11));
  LedDriver_TurnOn(11);
  CHECK_TRUE(LedDriver_IsOn(11));
}

TEST(Test_LedDriver, IsOff)
{
  CHECK_TRUE(LedDriver_IsOff(11));
  LedDriver_TurnOn(11);
  CHECK_FALSE(LedDriver_IsOff(11));
}

TEST(Test_LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
  CHECK_FALSE(LedDriver_IsOn(0));
  CHECK_TRUE(LedDriver_IsOff(0));
  CHECK_FALSE(LedDriver_IsOn(17));
  CHECK_TRUE(LedDriver_IsOff(17));
}
