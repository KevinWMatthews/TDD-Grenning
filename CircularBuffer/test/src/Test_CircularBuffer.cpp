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

TEST(CircularBuffer, NotEmptyThenEmpty)
{
  CircularBuffer_Put(buffer, 4567);
  CHECK_FALSE(CircularBuffer_IsEmpty(buffer));
  CircularBuffer_Get(buffer);
  CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, GetPutOneValue)
{
  CircularBuffer_Put(buffer, 4567);
  LONGS_EQUAL(4567, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, GetPutAFew)
{
  CircularBuffer_Put(buffer, 1);
  CircularBuffer_Put(buffer, 2);
  CircularBuffer_Put(buffer, 3);
  LONGS_EQUAL(1, CircularBuffer_Get(buffer));
  LONGS_EQUAL(2, CircularBuffer_Get(buffer));
  LONGS_EQUAL(3, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, Capacity)
{
  CircularBuffer b = CircularBuffer_Create(2);
  LONGS_EQUAL(2, CircularBuffer_Capacity(b));
  CircularBuffer_Destroy(b);
}
