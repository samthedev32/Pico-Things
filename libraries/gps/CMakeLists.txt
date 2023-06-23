add_library(pico_gps gps.h)

target_link_libraries(pico_gps pico_stdlib hardware_spi hardware_i2c hardware_adc)
target_include_directories(pico_gps PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

