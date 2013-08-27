cmake_minimum_required(VERSION 2.8)
project(TirfBarCode)
find_package(OpenCV REQUIRED)

#include(OpenCVConfig.cmake)
#include_directories(${OPENCV_INCLUDRE_DIR})

add_executable(TirfBarCode main.cpp)
target_link_libraries(TirfBarCode ${OpenCV_LIBS})
