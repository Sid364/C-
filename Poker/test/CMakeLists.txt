include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
    main.cpp
    TestCard.hpp
    TestRules.hpp
)

add_executable(test_runner ${SOURCE_FILES} Stack.hpp)
target_link_libraries(test_runner ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} PokerImpl)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
set (TEST test_runner)
enable_testing()