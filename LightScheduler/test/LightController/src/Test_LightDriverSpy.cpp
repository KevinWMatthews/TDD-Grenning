extern "C"
{
  #include "LightDriverSpy.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LightDriverSpy.h"

TEST_GROUP(LightDriverSpy)
{
  LightDriver lightDriver;

  void setup()
  {
    LightDriverSpy_Reset();
    lightDriver = LightDriverSpy_Create(1);
    LightDriverSpy_InstallInterface();
  }

  void teardown()
  {
    LightDriver_Destroy(lightDriver);
  }
};

TEST(LightDriverSpy, Create)
{
  LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, On)
{
  LightDriver_TurnOn(lightDriver);
  LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, Off)
{
  LightDriver_TurnOff(lightDriver);
  LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, RecordsLastIdLastTurnOn)
{
  LightDriver_TurnOff(lightDriver);
  LONGS_EQUAL(1, LightDriverSpy_GetLastId());
  LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetLastState());
}

TEST(LightDriverSpy, RecordsLastIdLastTurnOff)
{
  LightDriver_TurnOn(lightDriver);
  LONGS_EQUAL(1, LightDriverSpy_GetLastId());
  LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetLastState());
}
