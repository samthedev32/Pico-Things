add_library(pico_lcd st7789.h)

pico_generate_pio_header(pico_lcd ${CMAKE_CURRENT_LIST_DIR}/st7789_lcd.pio)

target_link_libraries(pico_lcd pico_stdlib hardware_pio pico_graphics)

target_include_directories(pico_lcd PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
