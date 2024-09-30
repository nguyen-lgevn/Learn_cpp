cmake_minimum_required (VERSION 2.8)
project (HelloWorld)
set (CMAKE_BUILD_TYPE Debug)
find_package (JNI REQUIRED)
find_package (Java REQUIRED)

add_jar()
