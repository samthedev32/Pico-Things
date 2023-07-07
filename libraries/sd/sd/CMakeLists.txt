add_library(pico_sd sd.h)

target_link_libraries(pico_sd pico_stdlib FatFs_SPI)

target_include_directories(pico_sd PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")