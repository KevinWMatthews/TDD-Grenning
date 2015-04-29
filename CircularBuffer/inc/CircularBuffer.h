#ifndef __CircularBuffer_H_
#define __CircularBuffer_H_

typedef struct CircularBufferStruct * CircularBuffer;

CircularBuffer CircularBuffer_Create(int size);
void CircularBuffer_Destroy(CircularBuffer self);

int CircularBuffer_IsEmpty(CircularBuffer self);
int CircularBuffer_IsFull(CircularBuffer self);
void CircularBuffer_Put(CircularBuffer self, int value);

#endif
