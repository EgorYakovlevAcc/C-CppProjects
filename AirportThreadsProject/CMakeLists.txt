cmake_minimum_required(VERSION 3.8)
project(AirportThreadsProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AirportLine.cpp AirportLine.h)
add_executable(AirportThreadsProject ${SOURCE_FILES} AirportLine.cpp AirportLine.h)
include_directories(C:/dst/mingw-std-threads-master/mingw-std-threads-master/)