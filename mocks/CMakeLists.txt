PROJECT(TDDEmbeddedC)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../lib)

SET(CMAKE_CXX_FLAGS ${ORIG_CXX_FLAGS})

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -pedantic -Werror")

ADD_LIBRARY(RuntimeErrorStub ./RuntimeErrorStub.c)
