cmake_minimum_required(VERSION 3.0)

project(LCG_Crack)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Wall -Wextra -Wpedantic -Werror -O3")

include_directories(include/)

add_executable(Crack
	src/LCGCrack.cc
	src/LCGSequence.cc
	src/LCG.cc
	src/Utils.cc)

