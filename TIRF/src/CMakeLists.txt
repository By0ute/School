#include(OpenCVConfig.cmake)
include_directories(${OPENCV_INCLUDRE_DIR})

add_executable(TirfBarCode main.cpp Pretrt.cpp Trt.cpp Axe.cpp BarCodeTrt.cpp TabInt.cpp)
target_link_libraries(TirfBarCode ${OpenCV_LIBS})
set(EXECUTABLE_OUTPUT_PATH ../)
