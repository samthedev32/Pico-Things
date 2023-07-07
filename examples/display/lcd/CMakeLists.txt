add_executable(lcd_example main.c)

target_link_libraries(lcd_example pico_stdio pico_lcd)

pico_add_extra_outputs(lcd_example)