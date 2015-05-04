extern "C"
{
  #include "Example.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_Example.h"

TEST_GROUP(Example)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(Example, DependencyCheck)
{
  LONGS_EQUAL(2, func(2));
}
