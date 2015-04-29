#include "CircularBuffer.h"
#include <stdlib.h>

typedef struct CircularBufferStruct
{
  int * values;    // The actual buffer
} CircularBufferStruct;

CircularBuffer CircularBuffer_Create(int capacity)
{
  CircularBuffer self = calloc(1, sizeof(CircularBufferStruct));    // was calloc(capacity,) but I don't know why.
  self->values = calloc(capacity + 1, sizeof(int));
  return self;
}

void CircularBuffer_Destroy(CircularBuffer self)
{
  free(self->values);
  free(self);
}
