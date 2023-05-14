add_executable(example_gps main.c)

target_link_libraries(example_gps pico_stdlib gps)

pico_enable_stdio_usb(example_gps 1)
pico_enable_stdio_uart(example_gps 0)

pico_add_extra_outputs(example_gps)