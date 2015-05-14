extern "C"
{
  #include "LightController.h"
  #include "LightDriver.h"
  #include "LightDriverSpy.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LightController.h"

TEST_GROUP(LightController)
{
  void setup()
  {
    LightController_Create();
    LightDriverSpy_AddSpiesToController();
  }

  void teardown()
  {
    LightController_Destroy();
  }
};

// This test should leak if the previous LightDriverSpy isn't destroyed,
// but I don't know how to detect leaks yet.
TEST(LightController, AllDriversDestroyed)
{
  for (int i = 0; i < MAX_LIGHTS; i++)
  {
    LightDriver spy = LightDriverSpy_Create(i);
    LONGS_EQUAL(TRUE, LightController_Add(i, (LightDriver)spy));
  }
}

TEST(LightController, TurnOn)
{
  LightController_On(7);
  LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(7));
}

TEST(LightController, TurnOff)
{
  LightController_On(1);
  LightController_Off(1);
  LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}

// This test should leak if the previous LightDriverSpy isn't destroyed,
// but I don't know how to detect leaks yet.
TEST(LightController, AddingDriverDestroysPrevious)
{
  LightDriver spy = LightDriverSpy_Create(1);
  LightController_Add(1, spy);
  LightController_Destroy();
}

TEST(LightController, ValidIdLowerRange)
{
  LightDriver spy = LightDriverSpy_Create(0);
  LONGS_EQUAL(TRUE, LightController_Add(0, spy));
}

TEST(LightController, ValidIdUpperRange)
{
  LightDriver spy = LightDriverSpy_Create(MAX_LIGHTS);
  LONGS_EQUAL(TRUE, LightController_Add(MAX_LIGHTS-1, spy));
}

TEST(LightController, InValidIdBeyondUpperRange)
{
  LightDriver spy = LightDriverSpy_Create(MAX_LIGHTS);
  LONGS_EQUAL(FALSE, LightController_Add(MAX_LIGHTS, spy));
  free(spy);
}

// TEST(LightController, RemoveExistingLightDriverSucceeds)
// {
//   CHECK(LightController_Remove(10));
// }

// TEST(LightController, RemovedLightDoesNothing)
// {
//     LightController_Remove(1);
//     LightController_TurnOn(1);
//     LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
//     LightController_TurnOff(1);
//     LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
// }

TEST(LightController, RejectsNullDrivers)
{
    LONGS_EQUAL(FALSE, LightController_Add(1, NULL));
}

// TEST(LightController, RemoveNonExistingLightDriverFails)
// {
//     CHECK(LightController_Remove(10));
//     CHECK(LightController_Remove(10) == FALSE);
// }
