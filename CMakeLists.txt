cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(chess LANGUAGES CXX)
set(CMAKE_CXX_COMPILER "g++")
list(APPEND CMAKE_CXX_FLAGS "-std=c++1z ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

add_executable(chess src/info.cpp src/board.cpp src/pawn.cpp src/knight.cpp src/king.cpp src/bishop.cpp src/rook.cpp src/queen.cpp src/game.cpp)