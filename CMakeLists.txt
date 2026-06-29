cmake_minimum_required(VERSION 3.18)
project(raytracing)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wextra -Wpedantic -Wunused-variable -Wunused-function -Wshadow -Werror -O3")
set(ANDROID_STL "c++_shared")

file(GLOB SOURCES src/*.cpp)
add_executable(raytracing ${SOURCES})

target_include_directories(raytracing PRIVATE include)
