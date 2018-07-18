cmake_minimum_required(VERSION 3.0.0)
PROJECT(socket_test)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pthread")

IF(NOT CMAKE_BUILD_TYPE)
# SET(CMAKE_BUILD_TYPE "Debug")
 SET(CMAKE_BUILD_TYPE "Release")
ENDIF(NOT CMAKE_BUILD_TYPE)

ADD_EXECUTABLE(main_send main_send.cpp SendNode.h)
ADD_EXECUTABLE(main_recv main_recv.cpp RecvNode.h)
ADD_EXECUTABLE(udp-recv udp-recv.cpp port.h SendNode.h RecvNode.h)
ADD_EXECUTABLE(udp-send udp-send.cpp port.h)

