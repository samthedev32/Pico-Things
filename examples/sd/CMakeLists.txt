add_executable(sd_example main.c)

target_link_libraries(sd_example pico_stdio pico_sd)

pico_add_extra_outputs(sd_example)