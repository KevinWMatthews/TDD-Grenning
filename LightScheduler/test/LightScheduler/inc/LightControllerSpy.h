#ifndef D_LightControllerSpy_H_
#define D_LightControllerSpy_H_

// Return values for our spy functions
enum
{
  LIGHT_ID_UNKNOWN = -1, LIGHT_STATE_UNKNOWN = -1,
  LIGHT_OFF = 0, LIGHT_ON = 1
};

int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);
int LightControllerSpy_GetLightState(int id);

#endif
