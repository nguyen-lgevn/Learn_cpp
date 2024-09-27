cmake_minimum_required(VERSION 3.6)
project (bench_mark_cpp)

set(CMAKE_CXX_STANDARD 14)
set (SOURCE_FILES main.cc)

add_executable(bench_mark ${SOURCE_FILES})
target_include_directories(bench_mark PRIVATE includes)
