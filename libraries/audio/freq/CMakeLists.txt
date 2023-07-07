add_library(pico_freq freq.h)

target_link_libraries(pico_freq pico_stdlib)

target_include_directories(pico_freq PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")