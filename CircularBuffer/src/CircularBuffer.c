#include "CircularBuffer.h"
#include <stdlib.h>

typedef struct CircularBufferStruct
{
  int count;      // Current number of entries
  int index;
  int outdex;
  int capacity;
  int* values;    // The actual buffer
} CircularBufferStruct;

CircularBuffer CircularBuffer_Create(int capacity)
{
  CircularBuffer self = calloc(1, sizeof(CircularBufferStruct));    // was calloc(capacity,) but I don't know why.
  self->values = calloc(capacity + 1, sizeof(int));
  self->capacity = capacity;
  return self;
}

void CircularBuffer_Destroy(CircularBuffer self)
{
  free(self->values);
  free(self);
}

int CircularBuffer_IsEmpty(CircularBuffer self)
{
  return self->count == 0;
}

int CircularBuffer_IsFull(CircularBuffer self)
{
  return self->count == self->capacity;
}

int CircularBuffer_Put(CircularBuffer self, int value)
{
  self->values[self->index++] = value;
  self->count++;
  if (self->index == self->capacity)
  {
    self->index = 0;
  }
}

int CircularBuffer_Get(CircularBuffer self)
{
  int value;
  self->count--;
  value = self->values[self->outdex++];
  if (self->outdex == self->capacity)
  {
    self->outdex = 0;
  }
  return value;
}

int CircularBuffer_Capacity(CircularBuffer self)
{
  return self->capacity;
}
