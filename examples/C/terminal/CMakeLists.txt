add_executable(example_terminal main.c)

target_link_libraries(example_terminal pico_stdlib c_terminal)

pico_add_extra_outputs(example_terminal)
