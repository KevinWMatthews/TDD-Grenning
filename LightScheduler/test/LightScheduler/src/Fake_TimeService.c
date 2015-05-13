#include "TimeService.h"
#include "Fake_TimeService.h"
#include "DataTypes.h"

static Time theTime;
WakeupCallback callback;
static int period;

// Internal functions
static void clearTime(void)
{
  theTime.minuteOfDay = TIME_UNKNOWN;
  theTime.dayOfWeek = TIME_UNKNOWN;
}

static void clearPeriodicAlarm(void)
{
  callback = NULL;
  period = -1;
}

// Create mock implementations for TimeService functions
void TimeService_Create(void)
{
  clearTime();
  clearPeriodicAlarm();
}

void TimeService_Destroy(void)
{
  clearTime();
  clearPeriodicAlarm();
}

void TimeService_GetTime(Time* timePtr)
{
  timePtr->minuteOfDay = theTime.minuteOfDay;
  timePtr->dayOfWeek = theTime.dayOfWeek;
}

void TimeService_SetPeriodicAlarmInSeconds(int alarmPeriod, WakeupCallback callbackFunctionPointer)
{
  period = alarmPeriod;
  callback = callbackFunctionPointer;
}

void TimeService_CancelPeriodicAlarmInSeconds(int alarmPeriod, WakeupCallback callbackFunctionPointer)
{
  if (callback == callbackFunctionPointer && period == alarmPeriod)
  {
    clearPeriodicAlarm();
  }
}

// Create fake time service functions to set and get from the dead drop
void Fake_TimeService_SetMinute(int minute)
{
  theTime.minuteOfDay = minute;
}

void Fake_TimeService_SetDay(int dayOfWeek)
{
  theTime.dayOfWeek = dayOfWeek;
}

WakeupCallback Fake_TimeService_GetAlarmCallback(void)
{
  return callback;
}

int Fake_TimeService_GetAlarmPeriod(void)
{
  return period;
}
