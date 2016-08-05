#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(led_driver);

int main(int argc, char** argv)
{
	return RUN_ALL_TESTS(argc, argv);
}
