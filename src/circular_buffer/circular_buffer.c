#include "circular_buffer/circular_buffer.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int *circular_buffer;
static size_t buffer_size;
static size_t buffer_size_max;
static int *head, *tail;
static int isEmpty;

static void walk_forth(int **ptr)
{
	if (*ptr == circular_buffer + buffer_size_max - 1)
		*ptr = circular_buffer;
	else
		(*ptr)++;
}

void CircularBuffer_Create(uint16_t max_num_elements)
{
	circular_buffer = malloc(max_num_elements * sizeof(int));
	buffer_size_max = max_num_elements;
	buffer_size = 0;
	isEmpty = 1;
	head = tail = circular_buffer;
}

void CircularBuffer_Destroy()
{
	free(circular_buffer);
}

int CircularBuffer_Pop(void)
{
	if (CircularBuffer_IsEmpty())
		return 0;

	int retval = *tail;
	walk_forth(&tail);

	if (head == tail)
		isEmpty = 1;

	return retval;
}

int CircularBuffer_Push(int value)
{
	if (head == tail && !isEmpty)
		return 0;

	if (isEmpty)
		isEmpty = 0;

	*head = value;
	walk_forth(&head);

	return 1;
}

int CircularBuffer_IsEmpty(void)
{
	return isEmpty;
}
