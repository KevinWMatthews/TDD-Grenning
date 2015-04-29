extern "C"
{
  #include "TimeService.h"
  #include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_FakeTimeService.h"

TEST_GROUP(FakeTimeService)
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
  LONGS_EQUAL(period, FakeTimeService_GetAlarmPeriod());
  LONGS_EQUAL(callback, FakeTimeService_GetAlarmCallback());
}

TEST(FakeTimeService, Create)
{
  Time time;
  TimeService_GetTime(&time);

  LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
  LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Destroy)
{
  Time time;
  TimeService_GetTime(&time);
  WakeupCallback callback;

  FakeTimeService_SetMinute(42);
  FakeTimeService_SetDay(MONDAY);
  TimeService_SetPeriodicAlarmInSeconds(43, callback);
  TimeService_Destroy();

  LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
  LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
  checkPeriodicAlarm(-1, NULL);
}

TEST(FakeTimeService, SetTime)
{
  Time time;
  FakeTimeService_SetMinute(42);
  FakeTimeService_SetDay(SATURDAY);

  TimeService_GetTime(&time);
  LONGS_EQUAL(42, time.minuteOfDay);
  LONGS_EQUAL(SATURDAY, time.dayOfWeek);
}

TEST(FakeTimeService, SetPeriodicAlarm)
{
  WakeupCallback callback;

  TimeService_SetPeriodicAlarmInSeconds(42, callback);
  checkPeriodicAlarm(42, callback);
}

TEST(FakeTimeService, CanelClearsCallback)
{
  WakeupCallback callback;

  TimeService_SetPeriodicAlarmInSeconds(42, callback);
  TimeService_CancelPeriodicAlarmInSeconds(42, callback);
  checkPeriodicAlarm(-1, NULL);
}

TEST(FakeTimeService, CanelWontClearWrongCallbackFunction)
{
  WakeupCallback callback, otherCallback;

  TimeService_SetPeriodicAlarmInSeconds(42, callback);
  TimeService_CancelPeriodicAlarmInSeconds(42, otherCallback);
  checkPeriodicAlarm(42, callback);
}

TEST(FakeTimeService, CanelWontClearWrongCallbackPeriod)
{
  WakeupCallback callback;
  int period = 42, otherPeriod = 43;

  TimeService_SetPeriodicAlarmInSeconds(period, callback);
  TimeService_CancelPeriodicAlarmInSeconds(otherPeriod, callback);
  checkPeriodicAlarm(period, callback);
}
