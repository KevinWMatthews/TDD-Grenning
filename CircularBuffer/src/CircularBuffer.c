#include "CircularBuffer.h"
// Is there a way to make the linker throw a warning if the FormatOutput() function isn't found?
// We need to find a way to avoid a segmentation fault without warning.
#include "Utils.h"
#include <stdlib.h>

enum {BUFFER_GUARD = -999};

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
  self->values[capacity] = BUFFER_GUARD;
  return self;
}

void CircularBuffer_Destroy(CircularBuffer self)
{
  free(self->values);
  free(self);
}

int CircularBuffer_VerifyIntegrity(CircularBuffer self)
{
  return self->values[self->capacity] == BUFFER_GUARD;
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
  if (self->count >= self->capacity)
  {
    return 0;
  }

  self->values[self->index++] = value;
  self->count++;
  if (self->index >= self->capacity)
  {
    self->index = 0;
  }
  return 1;
}

int CircularBuffer_Get(CircularBuffer self)
{
  int value;

  if (self->count <= 0)
  {
    return 0;
  }

  value = self->values[self->outdex++];
  self->count--;
  if (self->outdex >= self->capacity)
  {
    self->outdex = 0;
  }
  return value;
}

int CircularBuffer_Capacity(CircularBuffer self)
{
  return self->capacity;
}

void CircularBuffer_Print(CircularBuffer self)
{
  // Format output has rerouted (substituted for with a function pointer)
  // with FormatOutputSpy(). FormatOutputSpy() puts data in our spy buffer
  // (see FormatOutputSpy_Create() to find this buffer;
  //  FormatOutput_GetOutput() examines the data that was placed there).
  FormatOutput("Circular buffer content:\n<");

  FormatOutput(">\n");
}
