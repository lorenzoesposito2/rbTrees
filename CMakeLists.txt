cmake_minimum_required(VERSION 3.30)
project(rbTree)

set(CMAKE_CXX_STANDARD 20)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(rbTree main.cpp node.h tree.h tree.cpp)

# Add the executable for the tests
add_executable(rbTree_test test.cpp node.h tree.h tree.cpp)
target_link_libraries(rbTree_test gtest_main)

include(GoogleTest)
gtest_discover_tests(rbTree_test)