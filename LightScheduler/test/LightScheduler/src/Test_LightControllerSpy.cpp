extern "C"
{
  #include "LightController.h"
  #include "LightControllerSpy.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LightControllerSpy.h"

TEST_GROUP(LightControllerSpy)
{
  void setup()
  {
    LightController_Create();
  }

  void teardown()
  {
    LightController_Destroy();
  }
};

//*** The Tests! ***//
TEST(LightControllerSpy, Create)
{
  int i;

  LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
  LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
  for (i = 0; i < MAX_LIGHTS; i++)
  {
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLightState(i));
  }
}

TEST(LightControllerSpy, RememberTheLastLightIdControlled)
{
  LightController_On(10);
  LONGS_EQUAL(10, LightControllerSpy_GetLastId());
  LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, TurnLightOff)
{
  LightController_On(11);
  LightController_Off(11);

  LONGS_EQUAL(11, LightControllerSpy_GetLastId());
  LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberMultipleLightStates)
{
  LightController_On(0);
  LightController_Off(31);
  LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLightState(0));
  LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLightState(31));
}
