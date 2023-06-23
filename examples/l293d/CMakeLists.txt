add_executable(example_l293d main.c)

target_link_libraries(example_l293d pico_stdlib pico_l293d)

pico_add_extra_outputs(example_l293d)
