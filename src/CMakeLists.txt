include_directories(${TRPA_SOURCE_DIR}/src)

add_executable(App main_app.cpp VecParam.cpp Sign.cpp TestObj.cpp Parseur.cpp Base.cpp Learning.cpp Model.cpp)
set(EXECUTABLE_OUTPUT_PATH ../)

add_executable(Trt main_trt.cpp VecParam.cpp Sign.cpp TestObj.cpp Parseur.cpp Base.cpp Testing.cpp)
set(EXECUTABLE_OUTPUT_PATH ../)
