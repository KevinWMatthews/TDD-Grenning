extern "C"
{
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_Name.h"

TEST_GROUP(Name)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(Name, WiringCheck)
{
  FAIL("Start here!");
}
