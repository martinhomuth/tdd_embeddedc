#include "CppUTest/TestHarness.h"

TEST_GROUP(circular_buffer)
{

};

TEST(circular_buffer, CreatedBufferIsEmpty)
{
	LONGS_EQUAL(0, 0);
}
