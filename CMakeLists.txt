cmake_minimum_required(VERSION 3.13)
project("imgcomp")

set(CMAKE_CXX_STANDARD 17)
add_executable(imgcomp src/main.cpp src/util.cpp src/imgcomp.cpp)

include_directories(include)
