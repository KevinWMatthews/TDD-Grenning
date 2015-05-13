extern "C"
{
  #include "TimeService.h"
  #include "Fake_TimeService.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_Fake_TimeService.h"

TEST_GROUP(Fake_TimeService)
{
  void setup()
  {
    TimeService_Create();
  }

  void teardown()
  {
    TimeService_Destroy();
  }
};

static void checkPeriodicAlarm(int period, WakeupCallback callback)
{
  LONGS_EQUAL(period, Fake_TimeService_GetAlarmPeriod());
  LONGS_EQUAL(callback, Fake_TimeService_GetAlarmCallback());
}

TEST(Fake_TimeService, Create)
{
  Time time;
  TimeService_GetTime(&time);

  LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
  LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(Fake_TimeService, Destroy)
{
  Time time;
  TimeService_GetTime(&time);
  WakeupCallback callback;

  Fake_TimeService_SetMinute(42);
  Fake_TimeService_SetDay(MONDAY);
  TimeService_SetPeriodicAlarmInSeconds(43, callback);
  TimeService_Destroy();

  LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
  LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
  checkPeriodicAlarm(-1, NULL);
}

TEST(Fake_TimeService, SetTime)
{
  Time time;
  Fake_TimeService_SetMinute(42);
  Fake_TimeService_SetDay(SATURDAY);

  TimeService_GetTime(&time);
  LONGS_EQUAL(42, time.minuteOfDay);
  LONGS_EQUAL(SATURDAY, time.dayOfWeek);
}

TEST(Fake_TimeService, SetPeriodicAlarm)
{
  WakeupCallback callback;

  TimeService_SetPeriodicAlarmInSeconds(42, callback);
  checkPeriodicAlarm(42, callback);
}

TEST(Fake_TimeService, CanelClearsCallback)
{
  WakeupCallback callback;

  TimeService_SetPeriodicAlarmInSeconds(42, callback);
  TimeService_CancelPeriodicAlarmInSeconds(42, callback);
  checkPeriodicAlarm(-1, NULL);
}

TEST(Fake_TimeService, CanelWontClearWrongCallbackFunction)
{
  WakeupCallback callback, otherCallback;

  TimeService_SetPeriodicAlarmInSeconds(42, callback);
  TimeService_CancelPeriodicAlarmInSeconds(42, otherCallback);
  checkPeriodicAlarm(42, callback);
}

TEST(Fake_TimeService, CanelWontClearWrongCallbackPeriod)
{
  WakeupCallback callback;
  int period = 42, otherPeriod = 43;

  TimeService_SetPeriodicAlarmInSeconds(period, callback);
  TimeService_CancelPeriodicAlarmInSeconds(otherPeriod, callback);
  checkPeriodicAlarm(period, callback);
}
