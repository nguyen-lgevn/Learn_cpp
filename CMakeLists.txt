cmake_minimum_required(VERSION 3.4)

project(LearnCpp)

set (LEARN_CPP_VERSION_MAJOR 0)
set (LEARN_CPP_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "-Wall")

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package ( Threads )

file(GLOB_RECURSE LEARN_CPP_SOURCES "src/*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)

add_executable(Hello main.cpp ${LEARN_CPP_SOURCES})
target_link_libraries(Hello ${CMAKE_THREAD_LIBS_INIT})
# build tcp server - client
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tcp_server)

