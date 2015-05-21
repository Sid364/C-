cmake_minimum_required(VERSION 2.8.4)
project(Poker)

if (UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()



if (WIN32)
set(Boost_USE_STATIC_LIBS   ON)
add_definitions(/DBOOST_ALL_NO_LIB=1)
endif()

#set(BOOST_ROOT C:/Boost)


find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL "Boost not found")
endif()

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
