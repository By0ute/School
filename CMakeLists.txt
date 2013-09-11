cmake_minimum_required(VERSION 2.8)
project(TRPA)
#find_package(OpenCV REQUIRED)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

#include(OpenCVConfig.cmake)
#include_directories(${OPENCV_INCLUDRE_DIR})

#add_executable(App main.cpp VecParam.cpp Sign.cpp)
#add_executable(Trt main.cpp VecParam.cpp)
#target_link_libraries(TirfBarCode ${OpenCV_LIBS})
add_subdirectory(src)
