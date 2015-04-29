extern "C"
{
  #include "RandomMinute.h"
  #include <stdio.h>
  #include <string.h>
}

#include "CppUTest/TestHarness.h"
#include "Test_RandomMinute.h"

#define BOUND 30

TEST_GROUP(RandomMinute)
{
  int minute;

  void setup()
  {
    RandomMinute_Create(BOUND);
    srand(1);
  }

  void teardown()
  {
  }

  void AssertMinuteIsInRange(void)
  {
    if (minute < -BOUND || minute > BOUND)
    {
      printf("bad minute value: %d\n", minute);
      FAIL("minute out of range");
    }
  }
};


TEST(RandomMinute, GetIsInRange)
{
  for (int i = 0; i < 100; i++)
  {
    minute = RandomMinute_Get();
    AssertMinuteIsInRange();
  }
}

TEST(RandomMinute, AllValuesPossible)
{
  int hit[2*BOUND + 1];
  memset(hit, 0, sizeof(hit));
  int i;

  for (i = 0; i < 350; i++)
  {
    minute = RandomMinute_Get();
    AssertMinuteIsInRange();
    hit[minute + BOUND]++;
  }

  for (i = 0; i < 2*BOUND + 1; i++)
  {
    CHECK(hit[i] > 0);
  }
}
