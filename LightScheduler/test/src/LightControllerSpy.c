// #include "LightController.h"
// #include "LightControllerSpy.h"
// #include <string.h>

// // The dead drop (spy data)
// static int lastId;
// static int lastState;
// static int lights[MAX_LIGHTS];

// // The spy creates alternate implementations of these functions
// void LightController_Create(void)
// {
//   lastId = LIGHT_ID_UNKNOWN;
//   lastState = LIGHT_STATE_UNKNOWN;
//   memset(lights, LIGHT_STATE_UNKNOWN, sizeof(lights));
// }

// void LightController_Destroy(void)
// {
// }

// void LightController_On(int id)
// {
//   lights[id] = LIGHT_ON;
//   lastId = id;
//   lastState = LIGHT_ON;
// }

// void LightController_Off(int id)
// {
//   lights[id] = LIGHT_OFF;
//   lastId = id;
//   lastState = LIGHT_OFF;
// }


// // True spy functions ;)
// // Return the values that were stashed in the dead drop
// int LightControllerSpy_GetLastId(void)
// {
//   return lastId;
// }

// int LightControllerSpy_GetLastState(void)
// {
//   return lastState;
// }

// int LightControllerSpy_GetLightState(int id)
// {
//   return lights[id];
// }
