cmake_minimum_required(VERSION 3.13)
project(test)

set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp cplusplus11.hpp cplusplus14.hpp cplusplus17.hpp)