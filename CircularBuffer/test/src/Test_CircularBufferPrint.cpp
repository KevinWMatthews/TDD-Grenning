#include "CppUTest/TestHarness.h"

extern "C"
{
  #include "CircularBuffer.h"
  #include "Utils.h"
  #include "FormatOutputSpy.h"
  #include <stdio.h>
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

TEST(CircularBufferPrint, PrintEmpty)
{
  expectedOutput = "Circular buffer content:\n<>\n";
  CircularBuffer_Print(buffer);
  STRCMP_EQUAL(expectedOutput, actualOutput);
}
