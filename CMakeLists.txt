cmake_minimum_required(VERSION 3.13)
project("imgcomp")

set(PROJECT_VERSION_MAJOR 2)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)
add_executable(imgcomp src/main.cpp src/util.cpp src/util.h src/imgcomp.cpp src/imgcomp.h)

include_directories(include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Pack)
