#include "CppUTest/TestHarness.h"

extern "C" {
#include "circular_buffer/circular_buffer.h"
}

static const int BUFSIZE = 10;

TEST_GROUP(circular_buffer)
{
	void setup() {
		CircularBuffer_Create(BUFSIZE);
	}

	void teardown() {
		CircularBuffer_Destroy();
	}
};

TEST(circular_buffer, CreatedBufferIsEmpty)
{
	CHECK_TRUE(CircularBuffer_IsEmpty());
}

TEST(circular_buffer, PoppingFromEmptyBufferFails)
{
	CHECK_FALSE(CircularBuffer_Pop());
}

TEST(circular_buffer, PushingAndPoppingAnElementResultsInElement)
{
	int element = 234;
	CircularBuffer_Push(element);
	LONGS_EQUAL(element, CircularBuffer_Pop());
}

TEST(circular_buffer, PushingTwoElementsPreservesTheOrder)
{
	int elem1 = 233, elem2 = 432;
	CircularBuffer_Push(elem1);
	CircularBuffer_Push(elem2);
	LONGS_EQUAL(elem1, CircularBuffer_Pop());
	LONGS_EQUAL(elem2, CircularBuffer_Pop());
}

TEST(circular_buffer, AddingMoreThanSizeElementsResultsInError)
{
	for (int i = 0; i < BUFSIZE; i++)
		CHECK_TRUE(CircularBuffer_Push(i));
	CHECK_FALSE(CircularBuffer_Push(BUFSIZE));
}

TEST(circular_buffer, WrapAroundWorks)
{
	int i = 0;
	for (; i < BUFSIZE/2; i++)
		CircularBuffer_Push(i+10);
	for (int i = 0; i < (BUFSIZE/2 - 1); i++)
		CircularBuffer_Pop();
	CHECK_FALSE(CircularBuffer_IsEmpty());
	for (int i = 0; i < BUFSIZE - 1; i++)
		CHECK_TRUE(CircularBuffer_Push(i+20));
	for (int i = 0; i < BUFSIZE; i++)
		CHECK_TRUE(CircularBuffer_Pop());
}
