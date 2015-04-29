#include "CppUTest/TestHarness.h"

extern "C"
{
  #include "CircularBuffer.h"
  #include "FormatOutputSpy.h"
}

TEST_GROUP(CircularBuffer)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(CircularBuffer, Create)
{
  FAIL("CircularBuffer wired properly!");
}
