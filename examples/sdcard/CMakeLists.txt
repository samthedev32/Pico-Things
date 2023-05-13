add_executable(example_sdcard main.c)

target_link_libraries(example_sdcard pico_stdlib sdcard)

pico_add_extra_outputs(example_sdcard)