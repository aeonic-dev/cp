cmake_minimum_required(VERSION 3.25)
project(cp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(cp main.cpp)
include_directories(/usr/local/include)
