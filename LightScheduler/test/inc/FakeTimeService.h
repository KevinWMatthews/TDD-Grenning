#ifndef D_FakeTimeService_H_
#define D_FakeTimeService_H_

void FakeTimeService_SetMinute(int minute);   // minute ranges from 0 to 24*60 = 1440
void FakeTimeService_SetDay(int dayOfWeek);   // dayOfWeek ranges from 0 to 6
WakeupCallback FakeTimeService_GetAlarmCallback(void);
int FakeTimeService_GetAlarmPeriod(void);

#endif
