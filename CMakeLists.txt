cmake_minimum_required(VERSION 3.15)
project(Mobius)

set(CMAKE_CXX_STANDARD 14)

include_directories(Headers)

add_library(Mobius Sources/main.cpp)