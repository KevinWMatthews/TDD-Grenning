#ifndef D_LightScheduler_H_
#define D_LightScheduler_H_

#define MAX_EVENTS 128

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);

void LightScheduler_Wakeup(void);
int LightScheduler_ScheduleTurnOn(int id, int dayOfWeek, int minuteOfDay);
int LightScheduler_ScheduleTurnOff(int id, int dayOfWeek, int minuteOfDay);
void LightScheduler_ScheduleRemove(int id, int dayOfWeek, int minuteOfDay);
void LightScheduler_Randomize(int id, int dayOfWeek, int minuteOfDay);

// Return codes for LightScheduler_ScheduleTurnOn() and LightScheduler_ScheduleTurnOn()
enum
{
  LS_ID_OUT_OF_BOUNDS = -2,
  LS_TOO_MANY_EVENTS = -1,
  LS_OK = 0
};

#endif
