add_subdirectory(FatFs_SPI build)

add_library(pico_sdcard sdcard.h hw_config.c)

target_link_libraries(pico_sdcard pico_stdlib FatFs_SPI)
target_include_directories(pico_sdcard PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
