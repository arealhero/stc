cmake_minimum_required(VERSION 3.0)

project(StcTest)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Wall -Wextra -Wpedantic -Werror")

option(FMA "FMA instructions are available" OFF)
option(AVX "AVX instructions are available" OFF)

if(FMA)
	add_definitions(-D__FMA_AVAILABLE__)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfma")
endif(FMA)

if(AVX)
	add_definitions(-D__AVX_AVAILABLE__)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx")
endif(AVX)

add_compile_options(-march=native)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)

add_subdirectory(libs/googletest/)
add_subdirectory(libs/benchmark/)

add_subdirectory(Filter/)
add_subdirectory(LCG/)

