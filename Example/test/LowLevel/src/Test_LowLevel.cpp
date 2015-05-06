extern "C"
{
  #include "LowLevel.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_LowLevel.h"

TEST_GROUP(LowLevel)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(LowLevel, ReturnSame)
{
  LONGS_EQUAL(3, LowLevel_ReturnSame(3));
}

TEST(LowLevel, ReturnDouble)
{
  LONGS_EQUAL(6, LowLevel_ReturnDouble(3));
}
