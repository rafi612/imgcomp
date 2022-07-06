cmake_minimum_required(VERSION 3.13)
project("imgcomp")

set(PROJECT_VERSION 0.1.2)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 2)

set(CMAKE_CXX_STANDARD 17)
add_executable(imgcomp src/main.cpp src/util.cpp src/util.h src/imgcomp.cpp src/imgcomp.h)

configure_file (
  "src/config.h.in"
  "${CMAKE_BINARY_DIR}/config.h"
)

include_directories(build)

include_directories(include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Pack)
