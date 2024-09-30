cmake_minimum_required(VERSION 3.4)

project(Dispatcher)

set (LEARN_CPP_VERSION_MAJOR 0)
set (LEARN_CPP_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "-Wall")

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE LEARN_CPP_SOURCES "*.cc")
add_executable(Hello main.cc ${LEARN_CPP_SOURCES} )
