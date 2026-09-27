

cmake_minimum_required (VERSION 3.13)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

find_package(GTest CONFIG REQUIRED)
include (GoogleTest)

ADD_EXECUTABLE(TtrpgTest
    "ttrpg_test.cpp"  
    "dnd_test.cpp"
    "test_tools.h"
)
 
TARGET_LINK_LIBRARIES(TtrpgTest
PRIVATE 
    GTest::gtest 
    GTest::gtest_main
    TtrpgLib
)

gtest_discover_tests(TtrpgTest)
 
