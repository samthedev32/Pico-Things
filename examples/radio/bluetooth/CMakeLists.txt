add_executable(example_bluetooth main.c)

target_link_libraries(example_bluetooth pico_stdlib pico_bluetooth)

pico_enable_stdio_usb(example_bluetooth 1)
pico_enable_stdio_uart(example_bluetooth 0)

pico_add_extra_outputs(example_bluetooth)
