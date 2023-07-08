add_executable(turtle_v1 main.c)

target_link_libraries(turtle_v1 pico_stdlib pico_stepper)

pico_add_extra_outputs(turtle_v1)
