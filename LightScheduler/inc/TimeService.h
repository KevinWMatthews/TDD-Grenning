#ifndef D_TimeService_H_
#define D_TimeService_H_

typedef struct
{
  int minuteOfDay;
  int dayOfWeek;
} Time;

enum
{
  TIME_UNKNOWN = -1,
  SUNDAY = 0,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  WEEKDAY = 97,
  WEEKEND = 98,
  EVERYDAY = 99,
};

// Compiler magic!!
// Creates the typedef WakeupCallback for a function pointer:
// void (*)(void)
// i.e. a function pointer taking a single void parameter and returning a void
typedef void (*WakeupCallback)(void);

void TimeService_Create(void);
void TimeService_Destroy(void);
void TimeService_GetTime(Time* timePtr);
void TimeService_SetPeriodicAlarmInSeconds(int alarmPeriod, WakeupCallback callbackFunctionPointer);
void TimeService_CancelPeriodicAlarmInSeconds(int alarmPeriod, WakeupCallback callbackFunctionPointer);

#endif
