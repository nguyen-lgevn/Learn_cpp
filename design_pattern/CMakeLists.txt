#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/01_creational_patterns
#     ${CMAKE_CURRENT_SOURCE_DIR}/01_creational_patterns)

file(GLOB_RECURSE DESIGN_PATTERN_FILE 
    "*.cpp")

add_executable(design_pattern ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${DESIGN_PATTERN_FILE})
target_include_directories(design_pattern PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/01_creational_patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/02_structural_patterns
    ${CMAKE_CURRENT_SOURCE_DIR}/03_behavioral_patterns)

