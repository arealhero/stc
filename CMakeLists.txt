cmake_minimum_required(VERSION 3.0)

project(StcTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Wall -Wextra -Wpedantic -Werror")

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)

add_subdirectory(libs/googletest/)
add_subdirectory(libs/benchmark/)

add_subdirectory(Filter/)

