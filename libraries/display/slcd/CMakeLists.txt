add_library(pico_slcd slcd.h)

target_link_libraries(pico_slcd pico_stdlib pico_mathutil)

target_include_directories(pico_slcd PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
