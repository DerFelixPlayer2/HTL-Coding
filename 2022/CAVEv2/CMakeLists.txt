cmake_minimum_required(VERSION 3.20)
project(CAVEv2)

set(CMAKE_CXX_STANDARD 20)

add_executable(CAVEv2 grader.cpp cave.cpp cave.h)
