add_executable(example_list main.c)

target_link_libraries(example_list pico_stdlib c_list)

pico_add_extra_outputs(example_list)
