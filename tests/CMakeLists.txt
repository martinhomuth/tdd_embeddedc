PROJECT(TDDEmbeddedC)

# include project source for all subprojects
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../lib)

# include mocks only for test code
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../mocks)

# include CppUTest headers
INCLUDE_DIRECTORIES($ENV{CPPUTEST_HOME}/include)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -ggdb -include $ENV{CPPUTEST_HOME}/include/CppUTest/MemoryLeakDetectorMallocMacros.h")

LINK_DIRECTORIES($ENV{CPPUTEST_HOME}/lib -lCppUTest -lCppUTestExt)

# add cpputest library
ADD_LIBRARY(imp_cpputest STATIC IMPORTED)
SET_PROPERTY(TARGET imp_cpputest PROPERTY
             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/lib/libCppUTest.a)

# led_driver
ADD_LIBRARY(LedDriverTest ./led_driver/led_driver_test.cpp)
TARGET_LINK_LIBRARIES(LedDriverTest LedDriver)

ADD_EXECUTABLE(RunAllTests RunAllTests.cpp)
TARGET_LINK_LIBRARIES(RunAllTests imp_cpputest
  LedDriverTest
)
