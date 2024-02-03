cmake_minimum_required(VERSION 3.21)
project(Hanoi)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hanoi hanoi.cpp hanoi.h grader.cpp)
