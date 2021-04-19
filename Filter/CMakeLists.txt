cmake_minimum_required(VERSION 3.0)

project(Filter)

include_directories(include/)

add_executable(FilterSpecs specs/Filter.spec.cc)
add_executable(FilterBenchmark benchmarks/Filter.benchmark.cc)

target_link_libraries(FilterSpecs gtest)
target_link_libraries(FilterBenchmark benchmark::benchmark)

