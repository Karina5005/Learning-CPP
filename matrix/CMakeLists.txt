cmake_minimum_required(VERSION 3.5)
project(Matrix)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g)
include_directories(include)
add_executable(lab_14 src/main.cpp src/matrix.cpp include/matrix.h)
