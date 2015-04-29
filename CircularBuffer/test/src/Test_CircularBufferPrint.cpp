#include "CppUTest/TestHarness.h"

extern "C"
{
  #include "CircularBuffer.h"
  #include "Utils.h"
  #include "FormatOutputSpy.h"
}

TEST_GROUP(CircularBufferPrint)
{
  CircularBuffer buffer;
  const char * expectedOutput;
  const char * actualOutput;

  void setup()
  {
    UT_PTR_SET(FormatOutput, FormatOutputSpy);
    FormatOutputSpy_Create(100);
    actualOutput = FormatOutputSpy_GetOutput();
    buffer = CircularBuffer_Create(10);
  }

  void teardown()
  {
    CircularBuffer_Destroy(buffer);
    FormatOutputSpy_Destroy();
  }
};

TEST(CircularBufferPrint, WiringCheck)
{
  FAIL("CircularBufferPrint wiring check");
}
