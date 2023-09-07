add_executable(alarm main.c)

target_link_libraries(alarm pico_stdlib pico_gps)

pico_enable_stdio_usb(alarm 1)
pico_enable_stdio_uart(alarm 0)

pico_add_extra_outputs(alarm)
