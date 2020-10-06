cmake_minimum_required(VERSION 3.17)
project(MyMiniSTL)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyMiniSTL main.cpp src/allocator.h src/construct.h src/iterator.h)