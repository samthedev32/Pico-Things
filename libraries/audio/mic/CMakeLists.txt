add_library(pico_mic mic.h)

target_link_libraries(pico_mic pico_stdlib hardware_adc)

target_include_directories(pico_mic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")