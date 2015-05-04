extern "C"
{
  #include "LightController.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LightController.h"

TEST_GROUP(LightController)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(LightController, WiringCheck)
{
  FAIL("LightController wiring test!");
}
