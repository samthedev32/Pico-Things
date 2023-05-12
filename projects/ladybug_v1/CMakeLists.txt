add_executable(ladybug_v1 main.c)

target_link_libraries(ladybug_v1 pico_stdlib)

pico_add_extra_outputs(ladybug_v1)