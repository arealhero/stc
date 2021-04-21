cmake_minimum_required(VERSION 3.0)

project(StcTest)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Wall -Wextra -Wpedantic -Werror")

option(FMA_AVAILABLE "FMA instructions are available" OFF)

if(FMA_AVAILABLE)
	add_definitions(-D__FMA_AVAILABLE__)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfma")
endif(FMA_AVAILABLE)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)

add_subdirectory(libs/googletest/)
add_subdirectory(libs/benchmark/)

add_subdirectory(Filter/)
add_subdirectory(LCG/)

