#include "RandomMinute.h"
#include <stdlib.h>

static int bound;

void RandomMinute_Create(int boundary)
{
  bound = boundary;
}

int RandomMinute_Get_Impl(void)
{
  return bound - rand() % (bound * 2 + 1);
}

int (*RandomMinute_Get)(void) = RandomMinute_Get_Impl;
