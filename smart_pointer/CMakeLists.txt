cmake_minimum_required(VERSION 2.8.4)
project(smart_pointer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp smrt_ptr.h )
add_executable(smart_pointer ${SOURCE_FILES})
