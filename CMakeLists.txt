cmake_minimum_required(VERSION 3.7)
project(kadai5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c cmake-build-debug/practice.cpp cmake-build-debug/practice.h)
add_executable(kadai5 ${SOURCE_FILES})
