add_library(gps gps.h)

target_link_libraries(gps pico_stdlib hardware_spi hardware_i2c hardware_adc)
target_include_directories(gps PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

