#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(led_driver);
IMPORT_TEST_GROUP(circular_buffer);

int main(int argc, char** argv)
{
	return RUN_ALL_TESTS(argc, argv);
}
