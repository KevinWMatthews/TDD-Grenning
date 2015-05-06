extern "C"
{
  #include "MidLevel.h"   // Code under test
  #include "LowLevel.h"   // Mocked
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_MidLevel.h"

TEST_GROUP(MidLevel)
{
  void setup()
  {
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

int LowLevel_ReturnSame(int param)
{
  mock().actualCall("LowLevel_ReturnSame");
  return -1;
}

int LowLevel_ReturnDouble(int param)
{
  mock().actualCall("LowLevel_ReturnDouble");
  return -1;
}

TEST(MidLevel, EqualThenDouble)
{
  mock().expectOneCall("LowLevel_ReturnSame");
  mock().expectOneCall("LowLevel_ReturnDouble");

  LONGS_EQUAL(0, MidLevel_EqualThenDouble(8));
}
