cmake_minimum_required(VERSION 2.8)
project(TirfBarCode)
find_package(OpenCV REQUIRED)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

#include(OpenCVConfig.cmake)
include_directories(${OPENCV_INCLUDRE_DIR})

add_executable(TirfBarCode main.cpp Pretrt.cpp Trt.cpp Axe.cpp)
target_link_libraries(TirfBarCode ${OpenCV_LIBS})
