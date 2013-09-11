#cmake_minimum_required(VERSION 2.8)
#project(TRPA)
#find_package(OpenCV REQUIRED)

#list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

#include(OpenCVConfig.cmake)
#include_directories(${OPENCV_INCLUDRE_DIR})

include_directories(${TRPA_SOURCE_DIR}/src)

add_executable(App main_app.cpp VecParam.cpp Sign.cpp Base.cpp Learning.cpp)
set(EXECUTABLE_OUTPUT_PATH ../)

add_executable(Trt main_trt.cpp VecParam.cpp Sign.cpp Base.cpp Testing.cpp)
set(EXECUTABLE_OUTPUT_PATH ../)
#target_link_libraries(TirfBarCode ${OpenCV_LIBS})
