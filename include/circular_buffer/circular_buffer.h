#ifndef __CIRCULAR_BUFFER_H
#define __CIRCULAR_BUFFER_H

#include <stdint.h>

void CircularBuffer_Create(uint16_t);
void CircularBuffer_Destroy(void);
int CircularBuffer_IsEmpty(void);
int CircularBuffer_Pop(void);
int CircularBuffer_Push(int);

#endif
