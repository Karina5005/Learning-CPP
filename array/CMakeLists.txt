cmake_minimum_required(VERSION 3.5)
project(lab_13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
include_directories(include)

add_executable(lab_13 src/main.cpp include/my_array.h)