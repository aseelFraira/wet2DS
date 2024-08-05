cmake_minimum_required(VERSION 3.24)
project(wet2DS)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(wet2DS
        UnionFind.h
        UnionFind.cpp
        pirates24b2.h

        pirates24b2.cpp
        Pirate.h
        Pirate.cpp
        List.h
        Fleet.h
        Fleet.cpp
        wet2util.h HashTable.h)
