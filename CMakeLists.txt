cmake_minimum_required(VERSION 3.24)
project(wet2DS C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(wet2DS
        UnionFind.h)
