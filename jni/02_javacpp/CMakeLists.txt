cmake_minimum_required(VERSION 3.5)
project(javacpp)

FIND_PACKAGE(Java REQUIRED)
FIND_PACKAGE(JNI REQUIRED)
include(UseJava)

set (CMAKE_VERBOSE_MAKEFILE off)

message ("Java command: ${Java_JAVAH_EXECUTABLE} ${Java_JAVAC_EXECUTABLE} ${Java_JAVA_EXECUTABLE}")
message ("JNI include dir ${JNI_INCLUDE_DIRS}")
message ("JNI libraries ${JNI_LIBRARIES}")
message ("current source dir ${CMAKE_CURRENT_SOURCE_DIR}")

#file (JAVA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/HelloJNICpp.java)

add_jar(HelloJNICpp HelloJNICpp.java)
get_target_property(_jarFile HelloJNICpp JAR_FILE)
get_target_property(_classDir HelloJNICpp CLASSDIR)

set (_stubDir "${CMAKE_CURRENT_BINARY_DIR}")

message ("classpath ${_classDir} stubDir ${_stubDir}")
add_custom_command(
    OUTPUT HelloJNICpp.h
    COMMAND ${Java_JAVAH_EXECUTABLE} -verbose
        -classpath ${_classDir}
    -d ${_stubDir}
    -jni HelloJNICpp
    DEPENDS HelloJNICpp
    COMMENT "generate header file"
    )

include_directories(${JNI_INCLUDE_DIRS} ${_classDir} ${_stubDir})
add_library(hello MODULE HelloJNI.cpp HelloJNICpp.h)
#set_target_properties(hello PROPERTIES SUFFIX ".jnilib")
target_link_libraries(hello ${JNI_LIBRARIES})

#enable_testing()
add_custom_target(check
    COMMAND ${Java_JAVA_EXECUTABLE}
    -Djava.library.path=${CMAKE_CURRENT_BINARY_DIR}
    -cp ${_jarFile} HelloJNICpp
    )

#add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

