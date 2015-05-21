cmake_minimum_required(VERSION 3.1)
project(Graph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(Boost)

set(SOURCE_FILES main.cpp)
add_executable(Graph ${SOURCE_FILES} Graph.h)