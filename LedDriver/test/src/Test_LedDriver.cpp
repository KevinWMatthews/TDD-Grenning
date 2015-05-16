extern "C"
{
  #include "LedDriver.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LedDriver.h"

TEST_GROUP(LedDriver)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

#define NONSENSE_POINTER (LedDriver)~0
static LedDriver savedDriver = NONSENSE_POINTER;
// As the name states, this function should not be called.
// If it is, savedDriver will be changed from NONSENSE_POINTER to NULL.
// We can test for this condition to ensure that shouldNotBeCalled is never called.
static void shouldNotBeCalled(LedDriver self)
{
  savedDriver = self;
}

//*** The Tests! ***//
TEST(LedDriver, NullInterfaceDoesNotCrash)
{
  LedDriver_SetInterface(NULL);

  LedDriver_Destroy(NULL);
  LedDriver_TurnOn(NULL, 1);
  LedDriver_TurnOff(NULL, 1);
  LedDriver_TurnAllOn(NULL);
  LedDriver_TurnAllOff(NULL);
  LedDriver_IsOn(NULL, 1);
  LedDriver_IsOff(NULL, 1);

  POINTERS_EQUAL(NONSENSE_POINTER, savedDriver);
}