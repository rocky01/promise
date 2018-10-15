cmake_minimum_required(VERSION 3.1)

project(Promises)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -Wall -Os")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Os")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -Wall -g -finstrument-functions -O0")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -g -finstrument-functions -O0")

add_subdirectory(test)
