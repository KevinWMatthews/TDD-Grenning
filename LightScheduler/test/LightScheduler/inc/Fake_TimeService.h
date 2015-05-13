#ifndef D_Fake_TimeService_H_
#define D_Fake_TimeService_H_

void Fake_TimeService_SetMinute(int minute);   // minute ranges from 0 to 24*60 = 1440
void Fake_TimeService_SetDay(int dayOfWeek);   // dayOfWeek ranges from 0 to 6
WakeupCallback Fake_TimeService_GetAlarmCallback(void);
int Fake_TimeService_GetAlarmPeriod(void);

#endif
