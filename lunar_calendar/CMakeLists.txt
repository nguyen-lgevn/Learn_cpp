cmake_minimum_required(VERSION 3.6)

project(LunarCalendar VERSION 0.1)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_executable(LunarCalendar src/Lunar.c)

target_link_libraries (LunarCalendar m)
