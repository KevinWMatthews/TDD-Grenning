#include "MidLevel.h"
#include "LowLevel.h"

int MidLevel_EqualThenDouble(int param)
{
  LowLevel_ReturnSame(param);
  LowLevel_ReturnDouble(param);
  return 0;
}
