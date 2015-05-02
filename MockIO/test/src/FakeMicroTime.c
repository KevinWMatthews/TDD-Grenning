#ifdef __cplusplus
extern "C" {
#endif

#include "FakeMicroTime.h"

static uint32_t time;
static uint32_t increment;

void FakeMicroTime_Init(uint32_t start, uint32_t incr)
{
  time = start;
  increment = incr;
}

uint32_t MicroTime_Get(void)
{
  uint32_t t = time;
  time += increment;
  return t;
}

#ifdef __cplusplus
}
#endif
