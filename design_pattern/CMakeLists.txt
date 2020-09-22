cmake_minimum_required(VERSION 2.8)
project(design_pattern_cpp)

set (CMAKE_CXX_STANDARD 14)


#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/01_creational_patterns
#     ${CMAKE_CURRENT_SOURCE_DIR}/01_creational_patterns)

file(GLOB_RECURSE DESIGN_PATTERN_FILE
    main.cpp)
    #    ${CMAKE_CURRENT_SOURCE_DIR}/01_creational_patterns/*/*.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/02_structural_patterns/*/*.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/03_behavioral_patterns/*/*.cpp)

message("File: ${DESIGN_PATTERN_FILE}")

add_executable(design_pattern ${DESIGN_PATTERN_FILE})
target_include_directories(design_pattern PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/01_creational_patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/02_structural_patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/03_behavioral_patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/03_behavioral_patterns/mediator)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/03_behavioral_patterns/mediator)
