#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"
#include "DataTypes.h"

typedef struct
{
  int id;
  int minuteOfDay;
  int dayOfWeek;
  int event;
} ScheduledLightEvent;

enum
{
  UNUSED = -1,
  TURN_OFF = 0,
  TURN_ON = 1
};

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

//Prototypes
static int scheduleEvent(int id, int dayOfWeek, int minuteOfDay, int event);
static void processEventDueNow(Time* time, ScheduledLightEvent* lightEvent);
static BOOL doesLightRespondToday(Time* time, int dayOfWeek);
static void operateLight(ScheduledLightEvent* lightEvent);

void LightScheduler_Create(void)
{
  int i;

  for (i = 0; i < MAX_EVENTS; i++)
  {
    scheduledEvents[i].id = UNUSED;
  }

  // Pass the alarm period and a pointer to the function that should be called
  // each time the alarm period elapses
  TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightScheduler_Destroy(void)
{
  TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

int LightScheduler_ScheduleTurnOn(int id, int dayOfWeek, int minuteOfDay)
{
  return scheduleEvent(id, dayOfWeek, minuteOfDay, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int id, int dayOfWeek, int minuteOfDay)
{
  return scheduleEvent(id, dayOfWeek, minuteOfDay, TURN_OFF);
}

void LightScheduler_ScheduleRemove(int id, int dayOfWeek, int minuteOfDay)
{
  scheduledEvents[id].id = UNUSED;

  int i;

  for (i = 0; i < MAX_EVENTS; i++)
  {
    if (id == scheduledEvents[i].id &&
        dayOfWeek == scheduledEvents[i].dayOfWeek &&
        minuteOfDay == scheduledEvents[i].minuteOfDay )
    {
      scheduledEvents[i].id = UNUSED;
    }
  }
}

void LightScheduler_Wakeup(void)
{
  int i;
  Time timeNow;
  TimeService_GetTime(&timeNow);

  for (i = 0; i < MAX_EVENTS; i++)
  {
    processEventDueNow(&timeNow, &scheduledEvents[i]);
  }
}

void LightScheduler_Randomize(int id, int dayOfWeek, int minuteOfDay)
{}

static int scheduleEvent(int id, int dayOfWeek, int minuteOfDay, int event)
{
  int i;

  if (id < 0 || id >= MAX_LIGHTS)
    return LS_ID_OUT_OF_BOUNDS;

  for (i = 0; i < MAX_EVENTS; i++)
  {
    if (scheduledEvents[i].id == UNUSED)
    {
      scheduledEvents[i].dayOfWeek = dayOfWeek;
      scheduledEvents[i].minuteOfDay = minuteOfDay;
      scheduledEvents[i].event = event;
      scheduledEvents[i].id = id;
      return LS_OK;
    }
  }
  if (i == MAX_EVENTS)
  {
    return LS_TOO_MANY_EVENTS;
  }
}

static void processEventDueNow(Time* time, ScheduledLightEvent* lightEvent)
{
  if (lightEvent->id == UNUSED)
    return;

  if (!doesLightRespondToday(time, lightEvent->dayOfWeek))
    return;

  if (lightEvent->minuteOfDay != time->minuteOfDay)
    return;

  operateLight(lightEvent);
}

static BOOL doesLightRespondToday(Time* time, int reactionDay)
{
  int today = time->dayOfWeek;

  if (reactionDay == EVERYDAY)
    return TRUE;

  if (reactionDay == WEEKDAY && (today != SATURDAY && today != SUNDAY))
    return TRUE;

  if (reactionDay == WEEKEND && (today == SATURDAY || today == SUNDAY))
    return TRUE;

  if (reactionDay == today)
    return TRUE;

  return FALSE;
}

static void operateLight(ScheduledLightEvent* lightEvent)
{
  if (lightEvent->event == TURN_ON)
  {
    LightController_On(lightEvent->id);
  }
  else if (lightEvent->event == TURN_OFF)
  {
    LightController_Off(lightEvent->id);
  }
}
