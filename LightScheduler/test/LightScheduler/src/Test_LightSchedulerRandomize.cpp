extern "C"
{
  #include "LightScheduler.h"
  #include "LightController.h"
  #include "LightControllerSpy.h"
  #include "TimeService.h"
  #include "Fake_TimeService.h"
  #include "RandomMinute.h"
  #include "Fake_RandomMinute.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LightSchedulerRandomize.h"

TEST_GROUP(LightSchedulerRandomize)
{
  // Declare a function pointer
  int (*savedRandomMinute_Get)();

  void setup()
  {
    LightController_Create();
    LightScheduler_Create();
    // Substitute (and restore) a fake function for the production code
    UT_PTR_SET(RandomMinute_Get, Fake_RandomMinute_Get);
    // savedRandomMinute_Get = RandomMinute_Get;  // Accomplished with UT_PTR_SET
    // RandomMinute_Get = Fake_RandomMinute_Get;
  }

  void teardown()
  {
    LightController_Destroy();
    LightScheduler_Destroy();
    // RandomMinute_Get = savedRandomMinute_Get;  // Accomplished with UT_PTR_SET
  }

  // Hmmm, a little bit of duplication
  // Helper functions
  void setTimeTo(int day, int minute)
  {
    Fake_TimeService_SetDay(day);
    Fake_TimeService_SetMinute(minute);
  }
  void checkLightState(int id, int state)
  {
    if (id == LIGHT_ID_UNKNOWN)
    {
      LONGS_EQUAL(id, LightControllerSpy_GetLastId());
      LONGS_EQUAL(state, LightControllerSpy_GetLastState());
    }
    else
    {
      LONGS_EQUAL(state, LightControllerSpy_GetLightState(id));
    }
  }
};

IGNORE_TEST(LightSchedulerRandomize, TurnsOnEarly)
{
  Fake_RandomMinute_SetFirstAndIncrement(-10, 5);
  LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
  LightScheduler_Randomize(4, EVERYDAY, 600);

  setTimeTo(MONDAY, 600-10);

  LightScheduler_Wakeup();

  checkLightState(4, LIGHT_ON);
}
