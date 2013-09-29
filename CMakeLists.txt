cmake_minimum_required(VERSION 2.8)
project(TRPA)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

add_subdirectory(src)
