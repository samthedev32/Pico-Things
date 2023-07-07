add_executable(example_sd main.c)

target_link_libraries(example_sd pico_stdlib pico_sd)

pico_add_extra_outputs(example_sd)
