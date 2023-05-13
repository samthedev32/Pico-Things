add_subdirectory(FatFs_SPI build)

add_library(sdcard sdcard.h hw_config.c)

target_link_libraries(sdcard pico_stdlib FatFs_SPI)
target_include_directories(sdcard PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")