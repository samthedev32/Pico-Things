add_library(pico_gps gps.h)

target_link_libraries(pico_gps pico_stdlib pico_mathutil hardware_gpio hardware_uart)

target_include_directories(pico_gps PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
