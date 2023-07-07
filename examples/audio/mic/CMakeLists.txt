add_executable(mic_example main.c)

target_link_libraries(mic_example pico_stdio pico_mic)

pico_add_extra_outputs(mic_example)