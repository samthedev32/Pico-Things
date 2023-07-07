add_library(pico_rf vw.h vw.c)

target_link_libraries(pico_rf pico_stdlib hardware_clocks hardware_gpio)

target_include_directories(pico_rf PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
