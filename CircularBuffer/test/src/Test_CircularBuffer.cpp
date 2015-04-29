#include "CppUTest/TestHarness.h"

extern "C"
{
  #include "CircularBuffer.h"
  #include "FormatOutputSpy.h"
}

TEST_GROUP(CircularBuffer)
{
  CircularBuffer buffer;

  void setup()
  {
    buffer = CircularBuffer_Create(10);
  }

  void teardown()
  {
    CircularBuffer_Destroy(buffer);
  }
};

TEST(CircularBuffer, Create)
{

}

TEST(CircularBuffer, EmptyAfterCreation)
{
  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotFullAfterCreation)
{
  CHECK_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, NotEmpty)
{
  CircularBuffer_Put(buffer, 10046);
  CHECK_FALSE(CircularBuffer_IsEmpty(buffer));
}
