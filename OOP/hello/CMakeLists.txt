# Declare the project.
# CXX means that the project is written in C++.
project(hello CXX)

# We require CMake-2.8 in order to build the program.
cmake_minimum_required(VERSION 2.8)

# Enable compilation with C++11
set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")

# Add an executable program to be built from the
# given source code files.
add_executable(hello main.cpp hello.cpp)
