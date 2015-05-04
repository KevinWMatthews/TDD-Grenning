extern "C"
{
  #include "LightController.h"
  #include "LightDriverSpy.h"
}

#include "CppUTest/TestHarness.h"
#include "Test_LightController.h"

TEST_GROUP(LightController)
{
  void setup()
  {
    LightController_Create();
    LightDriverSpy_AddSpiesToController();
  }

  void teardown()
  {
    LightController_Destroy();
  }
};

TEST(LightController, WiringCheck)
{
  FAIL("LightController wiring test!");
}
