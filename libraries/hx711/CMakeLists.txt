add_library(pico_hx711 hx711.h)

target_link_libraries(pico_hx711 pico_stdlib hardware_pio)

target_include_directories(pico_hx711 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
