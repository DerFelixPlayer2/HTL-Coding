cmake_minimum_required(VERSION 3.21)
project(CAVE)

set(CMAKE_CXX_STANDARD 20)

add_executable(CAVE grader.cpp cave.cpp cave.h)
