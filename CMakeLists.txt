cmake_minimum_required(VERSION 3.2)
project(BinaryStorage)

set(CMAKE_CXX_STANDARD 17)

add_executable(BinaryStorage main.cpp
        Storage.cpp
        Storage.h
        BlockIO.cpp
        BlockIO.h
)
