add_executable(example_stepper main.c)

target_link_libraries(example_stepper pico_stdlib pico_stepper)

pico_add_extra_outputs(example_stepper)
