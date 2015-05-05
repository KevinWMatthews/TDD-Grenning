extern "C"
{
  #include "Ccode.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_Ccode.h"

TEST_GROUP(Ccode)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(Ccode, DependencyCheck)
{
  LONGS_EQUAL(2, Ccode_func(2));
}
