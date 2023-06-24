add_executable(ladybug_v2 main.c)

target_link_libraries(ladybug_v2 pico_stdlib hardware_adc pico_stepper pico_bluetooth)

pico_add_extra_outputs(ladybug_v2)
