add_executable(adc main.c)

target_link_libraries(adc pico_stdlib hardware_adc)

pico_enable_stdio_usb(adc 1)
pico_enable_stdio_uart(adc 0)

pico_add_extra_outputs(adc)
