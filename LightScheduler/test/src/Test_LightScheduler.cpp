extern "C"
{
  #include "LightScheduler.h"   // Code under test
  #include "LightController.h"
  #include "LightControllerSpy.h"
  #include "TimeService.h"
  #include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LightScheduler.h"

TEST_GROUP(LightScheduler)
{
  void setup()
  {
    LightController_Create();
    LightScheduler_Create();
  }

  void teardown()
  {
    LightController_Destroy();
    LightScheduler_Destroy();
  }
};

TEST_GROUP(LightSchedulerInitAndCleanup)
{
};

// Helper functions
void setTimeTo(int day, int minute)
{
  FakeTimeService_SetDay(day);
  FakeTimeService_SetMinute(minute);
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

// The tests!
TEST(LightScheduler, CreateDoesNotChangeTheLights)
{
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, NoScheduleNothingHappens)
{
  setTimeTo(MONDAY, 100);

  LightScheduler_Wakeup();

  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
  LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
  setTimeTo(MONDAY, 1199);

  LightScheduler_Wakeup();

  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
  LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
  setTimeTo(MONDAY, 1200);

  LightScheduler_Wakeup();

  checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
  LightScheduler_ScheduleTurnOff(4, EVERYDAY, 1200);
  setTimeTo(TUESDAY, 1200);

  LightScheduler_Wakeup();

  checkLightState(4, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleTuesdayButItsMonday)
{
  LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTuesdayAndItsTuesday)
{
  LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
  setTimeTo(TUESDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, WeekdayScheduleNotOperatedOnSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(SATURDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, WeekdayScheduleNotOperatedOnSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, WeekdayScheduleIsOperatedOnMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    LONGS_EQUAL(3, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleWeekendItsFriday)
{
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(FRIDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekendItsSaturday)
{
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(SATURDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekendItsMonday)
{
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTwoEventsAtTheSameTime)
{
  LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
  LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);
  setTimeTo(SUNDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);
  checkLightState(12, LIGHT_ON);
}

TEST(LightScheduler, RejectsTooManyEvents)
{
  int i;
  for (i = 0; i < MAX_EVENTS; i++)
  {
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
  }
  LONGS_EQUAL(LS_TOO_MANY_EVENTS, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}

TEST(LightScheduler, RemoveRecyclesScheduleSlot)
{
  int i;
  for (i = 0; i < MAX_EVENTS; i++)
  {
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
  }
  LightScheduler_ScheduleRemove(6, MONDAY, 600);
  LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}

TEST(LightScheduler, RemoveCorrectEventId)
{
  LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
  LightScheduler_ScheduleTurnOn(7, MONDAY, 600);

  LightScheduler_ScheduleRemove(6, MONDAY, 600);

  setTimeTo(MONDAY, 600);
  LightScheduler_Wakeup();
  checkLightState(6, LIGHT_STATE_UNKNOWN);
  checkLightState(7, LIGHT_ON);
}

TEST(LightScheduler, RemoveCorrectEventMinute)
{
  LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
  LightScheduler_ScheduleTurnOn(6, MONDAY, 700);

  LightScheduler_ScheduleRemove(6, MONDAY, 600);

  setTimeTo(MONDAY, 600);
  LightScheduler_Wakeup();
  checkLightState(6, LIGHT_STATE_UNKNOWN);

  setTimeTo(MONDAY, 700);
  LightScheduler_Wakeup();
  checkLightState(6, LIGHT_ON);
}

TEST(LightScheduler, RemoveCorrectEventDay)
{
  LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
  LightScheduler_ScheduleTurnOn(6, TUESDAY, 600);

  LightScheduler_ScheduleRemove(6, MONDAY, 600);

  setTimeTo(MONDAY, 600);
  LightScheduler_Wakeup();
  checkLightState(6, LIGHT_STATE_UNKNOWN);

  setTimeTo(TUESDAY, 600);
  LightScheduler_Wakeup();
  checkLightState(6, LIGHT_ON);
}

TEST(LightScheduler, AcceptValidLightIds)
{
  LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
  LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
  LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(MAX_LIGHTS-1, MONDAY, 600));
}

TEST(LightScheduler, RejectInvalidLightIds)
{
  LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
  LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(MAX_LIGHTS, MONDAY, 600));
}



// Change test group: LightSchedulerInitAndCleanup
TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
  LightScheduler_Create();
  POINTERS_EQUAL((void *)LightScheduler_Wakeup,
                 (void *)FakeTimeService_GetAlarmCallback());
  LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
  LightScheduler_Destroy();
}

TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
  LightScheduler_Create();
  LightScheduler_Destroy();
  POINTERS_EQUAL(NULL, (void *)FakeTimeService_GetAlarmCallback());
}
