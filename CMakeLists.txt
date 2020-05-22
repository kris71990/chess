cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(chess LANGUAGES CXX)
set(CMAKE_CXX_COMPILER "g++")
list(APPEND CMAKE_CXX_FLAGS "-std=c++1z ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

add_executable(chess "")
include(sourcelist.cmake)